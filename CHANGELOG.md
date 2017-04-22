# hswitch Changelog

## 17.04.1
- the hosts file is now actually stored
    - a backup will be created to `/etc/hosts.hswtich.bak`
- added version number and changelog
- the geometry and position of the user interface is now stored and will be 
  restored when the app starts

## 17.04.0
- CRUD and enable / disable host block entries
- edit hosts data for a host block entry 
- gathering of all enabled host blocks and adding it to `/etc/hosts`