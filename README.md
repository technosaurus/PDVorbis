PDVorbis
========

Public domain ogg vorbis player

The current version is really slow and uses a lot of CPU/RAM to start because
it decodes the entire file at once.  This can be improved by breaking it up
into chunks instead of using the included file decoder.  This should reduce the
size as well as CPU and RAM usage.