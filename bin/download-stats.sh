#!/bin/sh

# This script shows the download stats on GitHub. Update the id using the
# output of curl -s https://api.github.com/repos/msysgit/msysgit/releases
# 1.9.2
#id=${1:-268568}
# 1.9.4
#id=${1:-371088}
# 1.9.4.msysgit.1
#id=${1:-494232}
# 1.9.4.msysgit.2
id=${1:-591437}

curl -s https://api.github.com/repos/msysgit/msysgit/releases/$id/assets |
grep -e '"name":' -e '"download_count":'
