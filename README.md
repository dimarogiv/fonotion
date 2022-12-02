# Fonotion - notion taking app  
Simple and easy to use notion taking app created with ncurses  
## Table of contents
- [Introduction](#introduction)
- [How to use](#how-to-use)
- [Configuration](#configuration)
- [Status](#status)
- [Installation](#installation)
- [Technologies](#technologies)
- [Contribution](#contribution)
  
## Introduction
This project aims to make notion taking and reading process  
much easier. In this app you can easily crate a tree of notes in which  
one notes contain other notes itself. Also it makes a human-readeble  
database that you can open and easily read using any other text editor.  
  
## How to use
Start the app simply by entering `fonotion` in your console.  
Here you will see noting except for "Home" note content, which is empty  
by default. Here after clicking `e` you can start filling your note with  
your content.  
  
To create another notes you will want to determine a name and type for it.  
Simply write something like `/.name` and exit enter mode.  
  
Here `/` means that here is not some usual text but another note.  
`.` means that it's a simple task. Type of note determination will help  
you to search for notes of particular type, i. e. filter them by type.  
`name` determines a name of the note, it will be showed in the text too.  
You can also make different from the actual name text showed by specifying  
it in double quotes followed by white space ` `.  
To start editing your newly created note exit edit mode by clicking `Esc`  
key and go to it by moving in the view mode with arrows and clicking `Enter`
when the cursor is in the right place. You can also create new note in this  
note too performing exactly the same steps.  
  
## Configuration
This part of the document is not ready yet.  
  
## Status
The project is currently in active developing. Here is still a lot of plans  
not implemented yet, but we are working on it right now. Such as cloud  
storing, encrypting etc.

## Installation  
To install the app use the following commands:  
```
# git clone https://github.com/dimarogiv/fonotion.git  
# cd fonotion
# make
# mv fonotion /usr/bin
```
  
## Technologies
- C++ 11.3.0
- ncurses 6.3  
  
## Contribution  
This project contributed by:
- @VladSmyk

This list is not long, because you are not here.  
Text me in [telegram](t.me/dimonchik315) to contribute.  
  
This projects is freely distributable under GNU License.  
2022 - now.
