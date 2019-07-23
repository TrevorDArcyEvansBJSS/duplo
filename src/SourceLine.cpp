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

#include "SourceLine.h"

#include <sstream>

#include "SourceFile.h"
#include "HashUtil.h"

/** 
 * Creates a new text file. The file is accessed relative to current directory.
 */
SourceLine::SourceLine(std::string& line, int lineNumber){
    m_line = line;
    m_lineNumber = lineNumber;

    std::string cleanLine;

	//Remove all white space and noise (tabs etc)
	for(int i=0;i<(int)line.size();i++){
		if(line[i] > ' '){
			cleanLine.push_back(line[i]);
		}
	}

    // MD5 hash
    unsigned char* pDigest = HashUtil::getMD5Sum((unsigned char*)cleanLine.c_str(), (int)cleanLine.size());

	struct{
		long long high;
		long long low;
	} hashValue;
	
	memcpy(&hashValue, pDigest, sizeof(long long)*2);
	
	m_hashHigh = hashValue.high;
	m_hashLow = hashValue.low;

}

int SourceLine::getLineNumber(){
	return m_lineNumber;
}

bool SourceLine::equals(SourceLine* pLine){
	return (m_hashHigh == pLine->m_hashHigh && m_hashLow == pLine->m_hashLow);
}

std::string& SourceLine::getLine(){
    return m_line;
}

