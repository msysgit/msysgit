param([string]$path)

# You can download the latest git-tfs. zip file at https://github.com/git-tfs/git-tfs/downloads
if ($path -eq "" -or !(test-path $path)) {
  write-host "Usage: extract-git-tfs ""path-to-git-tfs.zip"""
  exit
}

$dir = split-path $MyInvocation.MyCommand.Definition
$tmp = join-path $([System.IO.Path]::GetTempPath()) $([System.IO.Path]::GetRandomFileName())
md $tmp | out-null
$shell = new-object -com shell.application
$zip = $shell.namespace((convert-path $path))
$destination = $shell.namespace($tmp)
$destination.Copyhere($zip.items())
rm "$tmp\*.pdb" -fo
cp "$tmp\*.*" $dir -fo
rm $tmp -r -fo 

write-host "Extracted $path."