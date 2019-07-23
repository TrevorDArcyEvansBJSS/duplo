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

#include "Duplo.h"

#include <fstream>
#include <sstream>

#include "StringUtil.h"
#include "HashUtil.h"
#include "TextFile.h"
#include "SourceFile.h"
#include "SourceLine.h"
#include "ArgumentParser.h"

Duplo::Duplo(std::string listFileName, int minLines, int minChars, bool ignorePrepStuff){
    m_listFileName = listFileName;
    m_minLines = minLines;
    m_minChars = minChars;
    m_ignorePrepStuff = ignorePrepStuff;
}

int Duplo::process(SourceFile* pSource1, SourceFile* pSource2, std::ostream& outFile){

	int m = pSource1->getNumOfLines();
	int n = pSource2->getNumOfLines();

    const char LCS_empty = 0;
    const char LCS_up = 1;
    const char LCS_left = 2;

	// Initialize tables
	int arrSize = m+1;
    char* b = new char[(m+1)*(n+1)];
	char* c = new char[(m+1)*(n+1)];
	
	for(int i = 0; i<=m; i++){
		c[i+arrSize*0] = LCS_empty;
	}
	for(int j = 0; j<=n; j++){
		c[0+arrSize*j] = LCS_empty;
	}

	// Compute LCS
	for(int i = 1; i<=m; i++){
		for(int j = 1; j<=n; j++){
			if(pSource1->getLine(i-1)->equals(pSource2->getLine(j-1))){
  				c[i+arrSize*j] = c[(i-1)+arrSize*(j-1)]+1;
  				b[i+arrSize*j] = LCS_left | LCS_up;
			} else if(c[(i-1)+arrSize*j]>=c[i+arrSize*(j-1)]) {
  				c[i+arrSize*j] = c[(i-1)+arrSize*j];
  				b[i+arrSize*j] = LCS_up;
			} else {
  				c[i+arrSize*j] = c[i+arrSize*(j-1)];
  				b[i+arrSize*j] = LCS_left;
			}
		}
	}

	// Display LCS
	int x = m;
	int y = n;
	std::vector<int> seq1Rev;
	std::vector<int> seq2Rev;
	
	while(x && y){
		if(b[x+arrSize*y]==(LCS_left | LCS_up)) {
  			seq1Rev.push_back(x-1);
  			seq2Rev.push_back(y-1);
  			x--; y--;
		} else {
			if(b[x+arrSize*y] == LCS_up){
  				x--;
			} else {
  				y--;
  			}
  		}
  	}

	delete[] b;
	delete[] c;

	std::vector<int> seq1;
	std::vector<int> seq2;
	
	for(int i=(int)seq1Rev.size()-1;i>=0;i--){
		seq1.push_back(seq1Rev[i]);
		seq2.push_back(seq2Rev[i]);
	}

	int start=-10;
	int lastLine1=-10;
	int lastLine2=-10;
	int count=0;
	
	int matched=0;
	
	for(int i=0;i<(int)seq1.size();i++){
		if(lastLine1+1 == seq1[i] && lastLine2+1 == seq2[i]){
			lastLine1++;
			lastLine2++;
			count++;
		} else {
			if(count >= m_minLines){
				std::ostringstream os;
				outFile << pSource1->getFilename() << "(" << pSource1->getLine(seq1[start])->getLineNumber() << ")" << std::endl;
				outFile << pSource2->getFilename() << "(" << pSource2->getLine(seq2[start])->getLineNumber() << ")" << std::endl;
				for(int j=0;j<count;j++){
					outFile << pSource1->getLine(seq1[start+j])->getLine() << std::endl;
				}
				matched++;
				outFile << std::endl;
			}
			lastLine1=seq1[i];
			lastLine2=seq2[i];
			start=i;
			count=0;
		}
	}
	
	return matched;
}

void Duplo::run(std::string outputFileName){

    std::ofstream outfile(outputFileName.c_str(), std::ios::out|std::ios::binary);
	
    if(!outfile.is_open()){
        std::cout << "Error: Can't open file: " << outputFileName << std::endl;
        return;
    }

	std::cout << "Loading and hashing files ... ";
	std::cout.flush();

	std::vector<SourceFile*> sourceFiles;
	
	TextFile listOfFiles(m_listFileName.c_str());
	std::vector<std::string> lines;
	listOfFiles.readLines(lines, true);
	
    int files = 0;
    int locs = 0;

	// Create vector with all source files
	for(int i=0;i<(int)lines.size();i++){
		if(lines[i].size() > 5){
			SourceFile* pSourceFile = new SourceFile(lines[i], m_minChars, m_ignorePrepStuff);
            if(pSourceFile->getNumOfLines() > 0){
                files++;
                sourceFiles.push_back(pSourceFile);
                locs+=pSourceFile->getNumOfLines();
            }
		}
	}
	
	std::cout << "done.\n\n";
	
    outfile << "Number of files: " << files << std::endl;
    outfile << "Lines of code: " << locs << std::endl << std::endl;

	// Compare each file with each other
	for(int i=0;i<(int)sourceFiles.size();i++){
		std::cout << sourceFiles[i]->getFilename();
		int issues = 0;
		
		for(int j=0;j<(int)sourceFiles.size();j++){
			if(i > j){
				issues+=process(sourceFiles[i], sourceFiles[j], outfile);
			}
		}

		if(issues > 0){
			std::cout << " found " << issues << " block(s)";
		} else {
			std::cout << " nothing found";
		}
		
		std::cout << std::endl;
	}
}

/**
 * Main routine
 *
 * @param argc  number of arguments
 * @param argv  arguments
 */
int main(int argc, char* argv[]){

	ArgumentParser ap(argc, argv);

	if(!ap.is("--help") && argc > 2){
		Duplo duplo(argv[argc-2], ap.getInt("-ml", 3), ap.getInt("-mc", 3), ap.is("-ip"));
		duplo.run(argv[argc-1]);
	} else {
		std::cout << "\nNAME\n";
		std::cout << "       Duplo - duplicate source code block finder\n\n";

		std::cout << "\nSYNOPSIS\n";
		std::cout << "       duplo [OPTIONS] [INTPUT_FILELIST] [OUTPUT_FILE]\n";

		std::cout << "\nDESCRIPTION\n";
		std::cout << "       Duplo is a tool to find duplicated code blocks within multiple\n";
		std::cout << "       C/C++/Java source code files.\n\n";

		std::cout << "       -ml              minimal block size in lines (default is 3)\n";
		std::cout << "       -mc              minimal characters in line (default is 3)\n";
		std::cout << "       -ip              ignore preprocessor directives\n";
		std::cout << "       INTPUT_FILELIST  input filelist\n";
		std::cout << "       OUTPUT_FILE      output file\n";

        std::cout << "\nAUTHOR\n";
		std::cout << "       Christian M. Ammann (cammann@giants.ch)\n\n";	
	}

    return 0;
}

