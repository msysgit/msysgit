param([string]$path)

if (!(test-path $path)) {
  write-host "Usage: extract-git-tfs \"path-to-git-tfs.zip\""
  exit
}

$bin = join-path (Split-Path -parent $MyInvocation.MyCommand.Definition) "..\..\bin"
$tmp = join-path $([System.IO.Path]::GetTempPath()) $([System.IO.Path]::GetRandomFileName())
md $tmp | out-null
$shell = new-object -com shell.application
$zip = $shell.namespace($path)
$destination = $shell.namespace($tmp)
$destination.Copyhere($zip.items())
rm "$tmp\*.pdb" -fo
cp "$tmp\*.*" $bin -fo
rm $tmp -r -fo 

write-host "Extracted $path to bin."