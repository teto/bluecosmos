/**
\author Matthieu C. alias Teto

\mainpage Introduction to Blue Cosmos Documentation

\section intro_sec Introduction

\bc is a shoot them up ( alias 'shmup' ) written in C++.\n
This manual is divided in the following sections :
- \subpage installation_page
- \subpage developement_page

\page installation_page Installation
\section install_section Installation
\subsection windows_subsection Under Windows

Retrieve the archive from the official site and then Double-click on it.Just follow the instructions
and you must be able to enjoy \bc.

\subsection linux_subsection Under linux

If you run either <a href="http://www.ubuntu.com">Ubuntu</a> or Debian

\page developement_page About development
 Compilation / Programing Conventions / Use of SVN / Use of Tracker
 * \section intro_sec Introduction
 \section
  \note This is a "\note" test
  In each class,declare variables in the alphabetical order.Actually,you then initialize them
  in the constructor in the same order to prevent warnings as:
  "/home/teto/docs/bc/src/engine/ship.h:18: warning: ‘%CResourceShip::mRange’ will be initialized after
  /home/teto/docs/bc/src/engine/ship.h:15: warning:   ‘%fus::CStaticMesh* %CResourceShip::mModel’
  /home/teto/docs/bc/src/engine/rsrc_ship.cpp:4: warning:   when initialized here"

  About the Style, C => class,I => Interface ( = Abstract ),T => typedef,S =Struct

  As the code is cross-platform,use upper and lower case carefully ( especially for #include since
 C++ is case-sensitive anyway ).



  Ceci est la page sur la compilation de blue cosmos
  \anchor test
  \ref test

  You just need to download the latest archive on the official website
  etc...
 **/
