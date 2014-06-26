
// =============
// Configuration
// =============

var bReturnBinDirOnly = false; // Return only the full path to "bin" directory relative to "Git" directory
var bUseSystemEnv = false; // Will use the "SYSTEM" environment instead of the "USER" environment
var bPersistentHome = false; // Will create a "HOME" variable in the specified environment


// ==============
// Initialization
// ==============

ParseArguments(WScript.Arguments);

// Standard Access Objects
var oWSHShell = WScript.CreateObject("WScript.Shell");
var oFSO = WScript.CreateObject("Scripting.FileSystemObject");

var oEnvUser = oWSHShell.Environment("USER");
var oEnvSystem = oWSHShell.Environment("SYSTEM");
var oEnvVolatile = oWSHShell.Environment("VOLATILE");
var oEnvTarget = oEnvUser;
if(bUseSystemEnv){
	oEnvTarget = oEnvSystem;
}

var sGitCmdDirPath = FindExecDirectory("git.exe");
var sGitBinDirPath = null;

var sSSHAuthSock = oEnvTarget("SSH_AUTH_SOCK");
var sSSHAgentPID = oEnvTarget("SSH_AGENT_PID");

var bStartSSHAgent = false;

var aReturn = new Array();

// =======
// Process
// =======

// If asked, return only the full path for Git's "bin" directory
if(bReturnBinDirOnly){
	aReturn.push(GetBinDirFromCmdDir(sGitCmdDirPath));
}else{
	// If asked, set the persistent user's HOME directory if none set
	if(bPersistentHome){
		if(oEnvTarget("HOMEDRIVE") != "" && oEnvTarget("HOMEPATH") != ""){
			oEnvTarget("HOME") = oWSHShell.ExpandEnvironmentStrings("%HOMEDRIVE%%HOMEPATH%");
		}else if(oEnvVolatile("HOMEDRIVE") != "" && oEnvVolatile("HOMEPATH") != ""){
			oEnvTarget("HOME") = oWSHShell.ExpandEnvironmentStrings("%HOMEDRIVE%%HOMEPATH%");
		}else{
			oEnvTarget("HOME") = oWSHShell.ExpandEnvironmentStrings("%USERPROFILE%");
		}
		// Pass "HOME" variable to parent
		aReturn.push("HOME=" + oEnvTarget("HOME"));
	}

	// Detect if need to launch a new "ssh-agent.exe"
	if(sSSHAgentPID == "" || sSSHAuthSock == ""){
		bStartSSHAgent = true;
	}else if(!ProcessExists(sSSHAgentPID, "ssh-agent.exe")){
		bStartSSHAgent = true;
	}

	// Search for SSH executable directory (relative as "..\bin" from "sGitCmdDirPath")
	if(oFSO.FolderExists(sGitCmdDirPath)){
		sGitBinDirPath = "";
		var aGitCmdDirPath = sGitCmdDirPath.split("\\");
		for(i=0;i<aGitCmdDirPath.length-1;i++){
			sGitBinDirPath += aGitCmdDirPath[i] + "\\";
		}
		sGitBinDirPath += "bin";
	}

	// if necessary, launch the "ssh-agent.exe"
	if(bStartSSHAgent){
		if(oFSO.FileExists(sGitBinDirPath + "\\ssh-agent.exe")){
			var sTmpFile = oFSO.GetSpecialFolder(2) + "\\" + oFSO.GetTempName();
			oWSHShell.Run("\"" + oEnvSystem("ComSpec") + "\" /c \"" + sGitBinDirPath + "\\ssh-agent.exe\" > " + sTmpFile, 0, true);
			if(oFSO.FileExists(sTmpFile)){
				var oTmpFile = oFSO.OpenTextFile(sTmpFile, 1, false, -2);
				var sReturned = oTmpFile.ReadAll();
				if(sReturned != ""){
					sSSHAuthSock = sReturned.match(/^SSH_AUTH_SOCK\s*=\s*[^;]+;.*$/img)
						.toString()
						.replace(/^SSH_AUTH_SOCK\s*=\s*/img,"")
						.replace(/;.*$/img,"");
					sSSHAgentPID = sReturned.match(/^SSH_AGENT_PID\s*=\s*[^;]+;.*$/img)
						.toString()
						.replace(/^SSH_AGENT_PID\s*=\s*/img,"")
						.replace(/;.*$/img,"");
					oEnvTarget("SSH_AUTH_SOCK") = sSSHAuthSock;
					oEnvTarget("SSH_AGENT_PID") = sSSHAgentPID;
				}
				oTmpFile.Close();
				oFSO.DeleteFile(sTmpFile);
			}
		}
	}

	// Pass "SSH_AUTH_SOCK" and "SSH_AGENT_PID" variables to parent
	aReturn.push("SSH_AUTH_SOCK=" + sSSHAuthSock);
	aReturn.push("SSH_AGENT_PID=" + sSSHAgentPID);
}

// Done
WScript.StdOut.Write(aReturn.join("\n"));
WScript.Quit();


// =========
// Functions
// =========

function FindExecDirectory(sExecName){
	var sDirPath = null;
	if(sExecName != ""){
		var aEnvPath = (oEnvUser("PATH") + ";" + oEnvSystem("PATH")).split(";");
		for(i in aEnvPath){
			if(aEnvPath[i] != ""){
				aEnvPath[i] = oWSHShell.ExpandEnvironmentStrings(aEnvPath[i]);
				if(aEnvPath[i].substring(aEnvPath[i].length-1) === "\\"){
					aEnvPath[i] = aEnvPath[i].substring(0, aEnvPath[i].length-1);
				}
				if(oFSO.FileExists(aEnvPath[i] + "\\" + sExecName)){
					sDirPath = aEnvPath[i];
					break;
				}
			}
		}
	}
	return sDirPath;
}

function GetBinDirFromCmdDir(sCmdDir, sRelative){
	var sReturn = "";
	if(typeof sRelative !== "string"){
		sRelative = "..\\bin";
	}
	if(sRelative.substring(sRelative.length-1) === "\\"){
		sRelative = sRelative.substring(0, sRelative.length-1);
	}
	sReturn = oFSO.GetAbsolutePathName(sCmdDir + "\\" + sRelative);
	if(oFSO.FolderExists(sReturn)){
		return sReturn;
	}
	return "";
}

function ParseArguments(oArguments){
	if(oArguments.length > 0){
		var i = 0;
		while(i < oArguments.length){
			var sArgument = oArguments(i);
			if(sArgument == "/bindir"){
				bReturnBinDirOnly = true;
			}else if(sArgument == "/help"){
				PrintUsage();
			}else if(sArgument == "/home"){
				bPersistentHome = true;
			}else if(sArgument == "/system"){
				bUseSystemEnv = true;
			}
			i += 1;
		}
	}
	return;
}

function PrintUsage(iErrorCode){
	if(typeof iErrorCode !== "numeric"){
		iErrorCode = 0;
	}
	WScript.Echo(
        "\nUsage : cscript.exe " + WScript.ScriptName + " [/bindir] [/home] [/system]" +
        "\n\nOptions :" +
        "\n  /bindir   Returns only the full path to \"bin\" directory relative to" +
        "\n            \"Git\" directory" +
        "\n  /home     Define a \"HOME\" environment variable" +
        "\n  /system   Use the \"SYSTEM\" environment instead of the \"USER\" environment"
    );
	WScript.Quit(iErrorCode);
}

function ProcessExists(iPID, sName){
	var oWmiService = GetObject("winmgmts:\\\\.\\root\\CIMV2");
	var sWqlQuery = "SELECT * FROM Win32_Process WHERE ProcessId='" + iPID + "'";
	var aProcesses = null;
	var bReturn = false;
	if(typeof sName !== "undefined"){
		sWqlQuery += " AND Name='" + sName + "'";
	}
	try{
		aProcesses = oWmiService.ExecQuery(sWqlQuery);
	}catch(error){
		// Move on...
	}
	ForEach(aProcesses, function(oProcess){
		bReturn = true;
		return;	// Should be first
	});
	oWmiService = null;
	return bReturn;
}

function ForEach(oCollection, func){
	if(oCollection !== null){
		for(var e = new Enumerator(oCollection); !e.atEnd(); e.moveNext()){
			func(e.item());
		}
	}
	return;
}
