/** \class Duplo
 * Duplo, main class
 *
 * @author  Christian Ammann (cammann@giants.ch)
 * @date  16/05/05
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _DUPLO_H_
#define _DUPLO_H_

#include <string>
#include <iostream>

class SourceFile;

class Duplo {
protected:
    std::string m_listFileName;
    int m_minLines;
    int m_minChars;
    bool m_ignorePrepStuff;

public:
    Duplo(std::string listFileName, int minLines, int minChars, bool ignorePrepStuff);
	void run(std::string outputFileName);
	int process(SourceFile* pSource1, SourceFile* pSource2, std::ostream& outFile);
};

#endif

