#!/bin/sh

# This script shows the download stats on GitHub. Update the id using the
# output of curl -s https://api.github.com/repos/msysgit/msysgit/releases/

id=${1:-268568}
curl -s https://api.github.com/repos/msysgit/msysgit/releases/$id/assets |
grep -e '"name":' -e '"download_count":'
