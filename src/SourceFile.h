/** \class SourceFile
 * Represents a source code file
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

#ifndef _SOURCEFILE_H_
#define _SOURCEFILE_H_

#include <string>
#include <vector>

#include "SourceLine.h"

class SourceFile {
protected:
    std::string m_fileName;

    int m_minChars;
    bool m_ignorePrepStuff;

    std::vector<SourceLine*> m_sourceLines;

	bool isSourceLine(std::string& line);
	void getCleanLine(std::string& line, std::string& cleanedLine);

public:
    SourceFile(std::string fileName, int minChars, bool ignorePrepStuff);
    
    int getNumOfLines();
    SourceLine* getLine(int index);
    std::string& getFilename();
    
};

#endif
