
// =============
// Configuration
// =============

var bConfigUseParentForGitRootDir = false; // Use parent directory from this script's path instead of searching in PATH environment variable
var bConfigSetGitRootDir = false; // Return the full path "Git" directory
var sConfigGitRootDirEnv = "PROCESS"; // Enviroment target for "bConfigSetGitRootDir"
var bConfigSetGitBinDir = false; // Return the full path to "bin" directory relative to "Git" directory
var sConfigGitBinDirEnv = "PROCESS"; // Enviroment target for "bConfigSetGitBinDir"
var bConfigSetHome = false; // Will create a "HOME" variable in the specified environment
var sConfigHomeEnv = "PROCESS"; // Enviroment target for "bConfigSetHome"
var sConfigHomePath = null; // Custom value (path) for "HOME" variable
var bConfigStartSSHAgent = false; // Start a "SSH agent" if none exists the specified environment and sets it in the specified environment
var sConfigSSHAgentEnv = "PROCESS"; // Enviroment target for "bConfigStartSSHAgent"
var sConfigSSHAgentVar = "PS"; // Variable(s) to collect for "bConfigStartSSHAgent"


// ==============
// Initialization
// ==============

// Standard Access Objects
var oWSHShell = WScript.CreateObject("WScript.Shell");
var oFSO = WScript.CreateObject("Scripting.FileSystemObject");

var oScriptFile = oFSO.GetFile(WScript.ScriptFullName);

var oEnvProcess = oWSHShell.Environment("PROCESS");
var oEnvUser = oWSHShell.Environment("USER");
var oEnvSystem = oWSHShell.Environment("SYSTEM");
var oEnvVolatile = oWSHShell.Environment("VOLATILE");

// Set configuration variables
ParseArguments(WScript.Arguments);

// Used variables for process
var sGitCmdDirPath = null;
var sGitRootDirPath = null;
var sGitBinDirPath = null;
if(bConfigUseParentForGitRootDir){
	sGitRootDirPath = GetFullPath(oFSO.GetParentFolderName(oScriptFile), "..", true);
}else{
	sGitCmdDirPath = FindExecDirectory("git.exe");
	sGitRootDirPath = GetFullPath(sGitCmdDirPath, "..", true);
}
sGitBinDirPath = GetFullPath(sGitRootDirPath, "bin", true);

// Array for returning information
var aReturn = new Array();


// =======
// Process
// =======

// If asked, set the GIT_ROOT_DIR directory from the specified environment
if(bConfigSetGitRootDir){
	var oEnvGitRootDirTarget = oWSHShell.Environment(sConfigGitRootDirEnv);
	// Note: Set only if it's not the same because setting the value may be slow
	if(oEnvGitRootDirTarget("GIT_ROOT_DIR") !== sGitRootDirPath){
		oEnvGitRootDirTarget("GIT_ROOT_DIR") = sGitRootDirPath;
	}
	// Pass "GIT_ROOT_DIR" variable to parent
	aReturn.push("GIT_ROOT_DIR=" + oEnvGitRootDirTarget("GIT_ROOT_DIR"));
}

// If asked, set the GIT_BIN_DIR directory from the specified environment
if(bConfigSetGitBinDir){
	var oEnvGitBinDirTarget = oWSHShell.Environment(sConfigGitBinDirEnv);
	// Note: Set only if it's not the same because setting the value may be slow
	if(oEnvGitBinDirTarget("GIT_BIN_DIR") !== sGitBinDirPath){
		oEnvGitBinDirTarget("GIT_BIN_DIR") = sGitBinDirPath;
	}
	// Pass "GIT_BIN_DIR" variable to parent
	aReturn.push("GIT_BIN_DIR=" + oEnvGitBinDirTarget("GIT_BIN_DIR"));
}

// If asked, set the HOME directory from the specified environment if none set
if(bConfigSetHome){
	var oEnvHomeTarget = oWSHShell.Environment(sConfigHomeEnv);
	var sHomePath = null;
	if(sConfigHomePath != null){
		sHomePath = oWSHShell.ExpandEnvironmentStrings(sConfigHomePath);
	}else{
		if(oEnvHomeTarget("HOMEDRIVE") != "" && oEnvHomeTarget("HOMEPATH") != ""){
			sHomePath = oWSHShell.ExpandEnvironmentStrings("%HOMEDRIVE%%HOMEPATH%");
		}else if(oEnvVolatile("HOMEDRIVE") != "" && oEnvVolatile("HOMEPATH") != ""){
			sHomePath = oWSHShell.ExpandEnvironmentStrings("%HOMEDRIVE%%HOMEPATH%");
		}else{
			sHomePath = oWSHShell.ExpandEnvironmentStrings("%USERPROFILE%");
		}
	}
	// Note: Set only if it's not the same because setting the value may be slow
	if(oEnvHomeTarget("HOME") !== sHomePath){
		oEnvHomeTarget("HOME") = sHomePath;
	}
	// Pass "HOME" variable to parent
	aReturn.push("HOME=" + oEnvHomeTarget("HOME"));
}

// If asked to start SSH agent, detect if we need to launch a new "ssh-agent.exe" before
if(bConfigStartSSHAgent){
	var oEnvSSHAgentTarget = oWSHShell.Environment(sConfigSSHAgentEnv);
	var sSSHAuthSock = oEnvSSHAgentTarget("SSH_AUTH_SOCK");
	var sSSHAgentPID = oEnvSSHAgentTarget("SSH_AGENT_PID");
	var bMustStartSSHAgent = false;
	if(sSSHAgentPID == "" && sSSHAuthSock == ""){
		bMustStartSSHAgent = true;
	}else if(!ProcessExists(sSSHAgentPID, "ssh-agent.exe")){
		bMustStartSSHAgent = true;
	}
	// If necessary, launch the "ssh-agent.exe"
	if(bMustStartSSHAgent){
		if(oFSO.FileExists(sGitBinDirPath + "\\ssh-agent.exe")){
			var sTmpFile = oFSO.GetSpecialFolder(2) + "\\" + oFSO.GetTempName();
			oWSHShell.Run("\"" + oEnvSystem("ComSpec") + "\" /c \"" + sGitBinDirPath + "\\ssh-agent.exe\" > " + sTmpFile, 0, true);
			if(oFSO.FileExists(sTmpFile)){
				var oTmpFile = oFSO.OpenTextFile(sTmpFile, 1, false, -2);
				var sReturned = oTmpFile.ReadAll();
				if(sReturned != ""){
					if(sConfigSSHAgentVar.indexOf("P") != -1){
						sSSHAgentPID = sReturned.match(/^SSH_AGENT_PID\s*=\s*[^;]+;.*$/img)
							.toString()
							.replace(/^SSH_AGENT_PID\s*=\s*/img,"")
							.replace(/;.*$/img,"");
						// Note: Set only if it's not the same because setting the value may be slow
						if(oEnvSSHAgentTarget("SSH_AGENT_PID") !== sSSHAgentPID){
							oEnvSSHAgentTarget("SSH_AGENT_PID") = sSSHAgentPID;
						}
					}
					if(sConfigSSHAgentVar.indexOf("S") != -1){
						sSSHAuthSock = sReturned.match(/^SSH_AUTH_SOCK\s*=\s*[^;]+;.*$/img)
							.toString()
							.replace(/^SSH_AUTH_SOCK\s*=\s*/img,"")
							.replace(/;.*$/img,"");
						// Note: Set only if it's not the same because setting the value may be slow
						if(oEnvSSHAgentTarget("SSH_AUTH_SOCK") !== sSSHAuthSock){
							oEnvSSHAgentTarget("SSH_AUTH_SOCK") = sSSHAuthSock;
						}
					}
				}
				oTmpFile.Close();
				oFSO.DeleteFile(sTmpFile);
			}
		}
	}
	// If asked, Pass "SSH_AUTH_SOCK" and/or "SSH_AGENT_PID" variables to parent
	if(sConfigSSHAgentVar.indexOf("P") != -1){
		aReturn.push("SSH_AGENT_PID=" + sSSHAgentPID);
	}
	if(sConfigSSHAgentVar.indexOf("S") != -1){
		aReturn.push("SSH_AUTH_SOCK=" + sSSHAuthSock);
	}
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
		var aEnvPath = (oEnvProcess("PATH") + ";" + oEnvUser("PATH") + ";" + oEnvSystem("PATH") + ";" + oEnvVolatile("PATH")).split(";");
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

function GetFullPath(sCmdDir, sRelative, bOnlyIfExists){
	if(typeof sCmdDir === "string"){
		if(typeof sRelative !== "string"){
			sRelative = "";
		}
		if(typeof bOnlyIfExists !== "boolean"){
			bOnlyIfExists = false;
		}
		var sReturn = "";
		if(sRelative.substring(sRelative.length-1) === "\\"){
			sRelative = sRelative.substring(0, sRelative.length-1);
		}
		sReturn = oFSO.GetAbsolutePathName(sCmdDir + "\\" + sRelative);
		if(oFSO.FolderExists(sReturn)){
			return sReturn;
		}
	}
	return null;
}

function GetFullEnvironmentTypeFromSeparator(sString, sSeparator, sDefault){
	if(typeof sDefault === "undefined"){
		sDefault = null;
	}
	if(sString.indexOf(sSeparator) != -1){
		var aString = sString.split(sSeparator);
		var sEnv = aString[1];
		if(typeof sEnv === "string"){
			if(sEnv.toUpperCase() == "P"){
				return "PROCESS";
			}else if(sEnv.toUpperCase() == "S"){
				return "SYSTEM";
			}else if(sEnv.toUpperCase() == "U"){
				return "USER";
			}else if(sEnv.toUpperCase() == "V"){
				return "VOLATILE";
			}
		}
	}
	return sDefault;
}

function ParseArguments(oArguments){
	if(oArguments.length > 0){
		var i = 0;
		while(i < oArguments.length){
			var sArgument = oArguments(i);
			// Set "GIT_ROOT_DIR" variable
			if(
				sArgument.toLowerCase() == "/gitrootdir" || sArgument.toLowerCase() == "/g" ||
				sArgument.toLowerCase().indexOf("/gitrootdir:") === 0 || sArgument.toLowerCase().indexOf("/g:") === 0
			){
				bConfigSetGitRootDir = true;
				// "GIT_ROOT_DIR" environment
				sConfigGitRootDirEnv = GetFullEnvironmentTypeFromSeparator(sArgument, ":", sConfigGitRootDirEnv);
			// Set "GIT_BIN_DIR" variable
			}else if(
				sArgument.toLowerCase() == "/gitbindir" || sArgument.toLowerCase() == "/b" ||
				sArgument.toLowerCase().indexOf("/gitbindir:") === 0 || sArgument.toLowerCase().indexOf("/b:") === 0
			){
				bConfigSetGitBinDir = true;
				// "GIT_BIN_DIR" environment
				sConfigGitBinDirEnv = GetFullEnvironmentTypeFromSeparator(sArgument, ":", sConfigGitBinDirEnv);
			// Set "HOME" variable
			}else if(
				sArgument.toLowerCase() == "/home" || sArgument.toLowerCase() == "/h" ||
				sArgument.toLowerCase().indexOf("/home:") === 0 || sArgument.toLowerCase().indexOf("/h:") === 0
			){
				bConfigSetHome = true;
				// "HOME" environment
				sConfigHomeEnv = GetFullEnvironmentTypeFromSeparator(sArgument, ":", sConfigHomeEnv);
				// "HOME" forced path
				if((i + 1) <= oArguments.length - 1){
					var sNextArgument = oArguments(i+1);
					if(sNextArgument.indexOf("/") !== 0){
						sConfigHomePath = sNextArgument;
						i++;
					}
				}
			// Use parent directory for Git root directory
			}else if(sArgument.toLowerCase() == "/parentdir" || sArgument == "/p"){
				bConfigUseParentForGitRootDir = true;
			// Start "SSH Agent"
			}else if(
				sArgument.toLowerCase() == "/startsshagent" || sArgument.toLowerCase() == "/s" ||
				sArgument.toLowerCase().indexOf("/startsshagent:") === 0 || sArgument.toLowerCase().indexOf("/s:") === 0
			){
				bConfigStartSSHAgent = true;
				// "SSH Agent" environment
				sConfigSSHAgentEnv = GetFullEnvironmentTypeFromSeparator(sArgument, ":", sConfigSSHAgentEnv);
				// "SSH Agent" variables
				if((i + 1) <= oArguments.length - 1){
					var sNextArgument = oArguments(i+1);
					if(sNextArgument.indexOf("/") !== 0){
						sConfigSSHAgentVar = sNextArgument.toUpperCase();
						i++;
					}
				}
			// Help
			}else if(sArgument.toLowerCase() == "/help" || sArgument == "/?"){
				PrintUsage(0);
			// Invalid argument
			}else{
				WScript.Echo(
					"\nThe argument \"" + sArgument + "\" is invalid." +
					"\nUse \"/?\" for available arguments."
				);
				WScript.Quit(1);
			}
			i++;
		}
	}else{
		PrintUsage(1);
	}
	return;
}

function PrintUsage(iErrorCode){
	WScript.Echo(
        "\nSet of additional environment utilities for MSysGit." +
        "\n\nUsage : cscript.exe [/nologo] " + WScript.ScriptName + 
        "\n        [/gitrootdir|/g[[:]environment]]" +
        "\n        [/gitbindir|/b[[:]environment]]" +
        "\n        [/parentdir|/p]" +
        "\n        [/home|/h[[:]environment] [homepath]]" +
        "\n        [/startsshagent|/s[[:]environment] [variables]]" +
        "\n\nOptions :" +
        "\n  /g           Defines a \"GIT_ROOT_DIR\" environment variable to the full path " +
        "\n               of the Git root directory which should be available in the" +
        "\n               \"PATH\" environment variable and returns as a \"set\" compatible" +
        "\n               command." +
        "\n  environment  Target environment for storing variables:" +
        "\n                P  Process [Default]" +
        "\n                S  System" +
        "\n                U  User (Persistent)" +
        "\n                V  User (Volatile/Session)" +
        "\n  /b           Defines a \"GIT_BIN_DIR\" environment variable to the full path " +
        "\n               of the \"bin\" directory relative to Git root directory which" +
        "\n               should be available in the \"PATH\" environment variable and" +
        "\n               returns as a \"set\" compatible command." +
        "\n  /p           Use the parent directory of this script as the Git root" +
        "\n               directory instead of searching in the \"PATH\" environment" +
        "\n               variable." +
        "\n               The current parent directory of this script is:" +
        "\n               \"" + GetFullPath(oFSO.GetParentFolderName(oScriptFile), "..") + "\"" +
        "\n  /h           Defines a \"HOME\" environment variable to the specified" +
        "\n               environment from a common logic or as set in the \"homepath\""+
        "\n               argument and returns as a \"set\" compatible command." +
        "\n  homepath     Value for \"HOME\" environment variable, all environment" + 
        "\n               variables from this value will be resolved by the current" +
        "\n               environment." +
        "\n               Default is \"%HOMEDRIVE%%HOMEPATH%\" if those variables exist," +
        "\n               otherwise \"%USERPROFILE%\"." +
        "\n  /s           Starts \"ssh-agent.exe\" if none set in the specified" +
        "\n               environment." +
        "\n               The specified variables will be defined or saved in the" +
        "\n               specified environment and returned as a \"set\" compatible" +
        "\n               command." +
        "\n  variables    Variables to collect from \"ssh-agent.exe\":" +
        "\n                P  SSH Agent PID [Default]" +
        "\n                S  SSH Authentication Socket as Unix path [Default]"
    );
	if(typeof iErrorCode !== "undefined"){
		WScript.Quit(iErrorCode);
	}
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
