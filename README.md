PDVorbis
========

Public domain ogg vorbis player


The current version starts slowly and uses a lot of CPU/RAM upfront because
it decodes the entire file at once.  This can be improved by breaking it up
into chunks instead of using the included file decoder.  This should reduce the
size as well as CPU and RAM usage - TODO.


This player uses Sean Barrett's public domain ogg-vorbis decoder.  The included
version has been "uncrustified" with https://github.com/bengardner/uncrustify
and assertions commented out (These should be the only C++ style comments,
since they will be removed with a proper DEBUG ifdef)