# duplo
C/C++/Java Duplicate Source Code Block Finder

(http://duplo.sourceforge.net/)

https://github.com/dlidstrom/Duplo


________________________________________________________________________________

Duplo (C/C++/Java Duplicate Source Code Block Finder)

Version 0.1.3 Readme File, May 2005
________________________________________________________________________________

## CONTENTS
 1. GENERAL INFORMATION
 2. SYSTEM REQUIREMENTS
 3. LICENSE
________________________________________________________________________________

### 1 GENERAL INFORMATION

Duplicated source code blocks can harm maintainability of software systems.
Duplo is a tool to find duplicated code blocks within multiple C/C++/Java 
source files.

- Sample Output ----------------------------------------------------------------

```
src\engine\geometry\simple\TorusGeometry.cpp(56)
src\engine\geometry\simple\SphereGeometry.cpp(54)
	pBuffer[currentIndex*size+3]=(i+1)/(float)subdsU;
	pBuffer[currentIndex*size+4]=j/(float)subdsV;
	currentIndex++;
	pPrimitiveBuffer->unlock();

src\engine\geometry\subds\SubDsGeometry.cpp(37)
src\engine\geometry\SkinnedMeshGeometry.cpp(45)
    pBuffer[i*size+0]=m_ct[0]->m_pColors[i*3];
    pBuffer[i*size+1]=m_ct[0]->m_pColors[i*3+1];
    pBuffer[i*size+2]=m_ct[0]->m_pColors[i*3+2];
```
--------------------------------------------------------------------------------

#### 1.1 OPTIONS

Run `duplo --help` on the command line to see detailed options.

#### 1.2 FEEDBACK AND BUG REPORTING

Please send Feedback and Bug Reports to:

cammann@giants.ch

duplo@bjss.com

#### 1.3 FILE LIST GENERATION

Generate a list of all files of a directory with:

Windows
```
dir /s /b /a-d *.cpp *.h > myFiles.lst`
```

UNIX
```
 find -name "*.cpp" > cppList.lst
 find -name "*.h" > includeList.lst
 cat cppList.lst includeList.lst > all.lst
```
________________________________________________________________________________

### 2 SYSTEM REQUIREMENTS

Duplo needs about two times the memory of the total source code size. So if
your Source code is about 120MB it requires 240MB.
________________________________________________________________________________

### 3 LICENSE

Duplo is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
________________________________________________________________________________
                                   2005, Christian M. Ammann (cammann@giants.ch)                                                            