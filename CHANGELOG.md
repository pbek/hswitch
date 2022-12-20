# hswitch Changelog

## 22.12.0
- update qmarkdowntextedit

## 18.10.0
- added support for `sudo -A`, since `kdesudo` is gone now

## 18.08.0
- you can now choose to don't get the message boxes to generate the hosts 
  file and the success message box any more
    - there also is a new menu entry to reset the message boxes again 

## 18.05.0
- [QMarkdownTextEdit](https://github.com/pbek/qmarkdowntextedit) (without 
  highlighting) is now used as text-editor to make use of the search-feature
  and various shortcuts
    - you can now search in your host-entries with <kbd>Ctrl</kbd> + <kbd>F</kbd>
 
## 18.03.0
- the text-edit for the host entries now only takes plain text

## 17.04.2
- minor design and user interface text changes
- added a confirmation dialog before writing the host file

## 17.04.1
- the hosts file is now actually stored
    - a backup will be created to `/etc/hosts.hswitch.bak`
- added version number and changelog
- the geometry and position of the user interface is now stored and will be 
  restored when the app starts

## 17.04.0
- CRUD and enable / disable host block entries
- edit hosts data for a host block entry 
- gathering of all enabled host blocks and adding it to `/etc/hosts`
