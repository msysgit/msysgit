#!/bin/sh

# Make sure that the working directory is clean and does not have untracked
# files; otherwise our semi-automatic finding the new files will not work!

die () {
	echo "$*" >&2
	exit 1
}

check_pristine () {
	(cd / &&
	 git diff-files --quiet &&
	 git diff-index --cached --quiet HEAD &&
	 others="$(git ls-files --exclude-standard --others)" &&
	 test -z "$others") ||
		die "State not pristine enough for successful package update"
}

# Remove old files stored in fileList.txt
pre_install () {
	test -z "$FILELIST" && {
		echo "No file list specified for pre_install"
		exit 1
	}
	! test -s "$FILELIST" ||
		cat "$FILELIST" | (cd / && xargs git rm --ignore-unmatch) ||
		exit
	INDEX=$(/share/msysGit/pre-install.sh)
}

# update the index 
post_install () {
	/share/msysGit/post-install.sh $INDEX "Install $package $version" ||
	exit

	(cd / && 
	 git show --diff-filter=AM --name-only |
	 sed -e "s/^/\//" > "$FILELIST" &&
	 git add "$FILELIST" &&
	 git commit -C HEAD --amend "$FILELIST") ||
	exit

	echo "Successfully built and installed $package $version"
	echo
}

download () {
	test -z "$tar" &&
		die "Script did not specify an archive"
	test -f "$tar" || {
		echo "Downloading $tar ..."
		curl $url/$tar -o $tar || exit
	}
}

extract () {
	test -z "$d" &&
		die "Script did not specify a directory"
	test -d "$d" || {
		echo "Unpacking $tar ..."
		case "$tar" in
		*.tar.gz|*.tgz)
			tar -xzf "$tar"
			;;
		*.tar.bz2|*.tbz)
			tar -xjf "$tar"
			;;
		*.zip)
			unzip "$tar"
			;;
		esac || exit
	}
}

apply_patches () {
	test -d "$d"/.git && return
	patchdir="$(pwd)"/patches
	(cd "$d" &&
	 git init &&
	 git config core.autocrlf false &&
	 git add . &&
	 git commit -m initial &&
	 for p in "$patchdir"/*.patch
	 do
		git am "$p" || exit
	 done) ||
	exit
}

setup () {
	test -z "$d" &&
		die "Script did not specify a directory"
	test -f "$d/Makefile" ||
		(cd "$d" && ./configure $configure_options) || exit
}

compile () {
	test -z "$d" &&
		die "Script did not specify a directory"
	(cd "$d" && make) || exit
}

download_extract_setup_and_compile () {
	download &&
	extract &&
	setup &&
	compile || exit
}
