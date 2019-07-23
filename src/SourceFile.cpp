/**
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

#include "SourceFile.h"

#include <sstream>
#include <iostream>

#include "TextFile.h"
#include "StringUtil.h"

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif
#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif


SourceFile::SourceFile(std::string fileName, int minChars, bool ignorePrepStuff){
    m_fileName = fileName;
 	m_minChars = minChars;
    m_ignorePrepStuff = ignorePrepStuff;

 	TextFile listOfFiles(m_fileName.c_str());

    std::vector<std::string> lines;
    listOfFiles.readLines(lines, false);
	
    int openBlockComments = 0;
	for(int i=0;i<(int)lines.size();i++){
        
        std::string tmp;
        std::string& line = lines[i];

        int lineSize = (int)line.size();
        for(int j=0;j<(int)line.size();j++){
            if(line[j] == '/' && line[MIN(lineSize-1, j+1)] == '*'){
                openBlockComments++;
            }

            if(openBlockComments <= 0){
                tmp.push_back(line[j]);
            }

            if(line[MAX(0, j-1)] == '*' && line[j] == '/'){
                openBlockComments--;
            }
        }

		std::string cleaned;
		getCleanLine(tmp, cleaned);
		
		if(isSourceLine(cleaned)){
			m_sourceLines.push_back(new SourceLine(cleaned, i));
		}
	}
}

void SourceFile::getCleanLine(std::string& line, std::string& cleanedLine){

    // Remove single line comments
	int lineSize = (int)line.size();
    for(int i=0;i<(int)line.size();i++){
		if(i < lineSize-2 && line[i] == '/' && line[i+1] == '/'){
            break;
        }
        
		cleanedLine.push_back(line[i]);
	}
}

bool SourceFile::isSourceLine(std::string& line){
	std::string tmp = StringUtil::trim(line);

    if(m_ignorePrepStuff && tmp[0] == '#'){
        return false;
    }

    return ((int)tmp.size() >= m_minChars);
}

int SourceFile::getNumOfLines(){
	return (int)m_sourceLines.size();
}

SourceLine* SourceFile::getLine(int index){
	return m_sourceLines[index];
}

std::string& SourceFile::getFilename(){
	return m_fileName;
}
