#include<vector>
#include<string>
#include<iostream>
#include<cstdio>

#include<strparse.h>

/*
Copy & idea from "https://www.codegrepper.com/code-examples/cpp/c%2B%2B+string+to+vector+using+delimiter"
*/
int indx(std::string main, std::string substr, int idx) {
	int iIdx = -1;
	size_t sidx = 0;
	switch(idx) {
		case -1:
			sidx = main.find_last_of(substr);
			if(sidx==std::string::npos) { 
				return -1;
			}
		case 0: 
			idx = 1;
			break;

	}
	int iCurOccurrence = 0;
	while ( (iCurOccurrence != idx) && (iCurOccurrence < main.size()) ) {
		sidx++;
		std::cout << "nigger\n";
		sidx = main.find(substr, sidx);
		if(sidx==std::string::npos) return -1;
		iCurOccurrence++;
		iIdx = int(sidx);
	}
	return iIdx;
}

std::vector<std::string> getVec() {
	std::vector<std::string>  ret;
	std::string str( "12.13.12.1" ), sCur;
	int len = std::string{"."}.length();
	int in = 1;
	int r1=0, r0=indx(str, std::string{"."}, in);
	if(r0==-1) {
		return ret;
	}
	while(r0!=-1) {
		std::string sCur = str.substr( (r1 + len) , r0 - (r1 + len));
	      ret.push_back(sCur);
	      r1 = r0;
	      in++;
	      r0 = indx(str,std::string{"."},in);
/*
		std::string cur = str.substr(r1 + str.length(), r0 - (r1 + str.length()));
		//ret.push_back(cur);
		r1=r0;
		in++;
		r0 = indx(str, std::string{"."}, in);
*/
	}

	return ret;
}

/*
Copy & idea from "https://www.codegrepper.com/code-examples/cpp/c%2B%2B+string+to+vector+using+delimiter"
*/


void t(char *delim) {
	std::string tst("12.1.1.1"); // BUG: check for three only possible for now
	std::vector<std::string> vec;
	char *tmpbuf = (char*)malloc(sizeof(char)*400); //[tst.size()];
	int i=0;
	for(auto ss=tst.begin(); ss<tst.end();ss++) {
		if(*ss==(int)delim[0]) {
			vec.push_back(tmpbuf);
			printf("%s\n", (char*)tmpbuf);
			ss+=1;
			tmpbuf = (char*)realloc(tmpbuf, i+1); //TODO find out why realloc or malloc does not work
		}
		else {
			tmpbuf[i] = *ss;
			std::cout << (int)*ss	;
		}
		i++;
	}

	std::cout << vec.at(0);
}

const std::vector<std::string> parseIpv4(const char *addr) { // only works for 3 part ipv4 address
	std::string str(addr);
	char *delim = ".";
	char *tmpbuf = (char*)malloc(sizeof(char)*4); //[tst.size()];
	std::vector<std::string> vec;
	int i=0;
	for(auto ss=str.begin();ss<=str.end();ss++) {
		if(*ss==(int)delim[0]) {
			vec.push_back(std::string{tmpbuf});
			ss+=1;
			i=0;
			tmpbuf = new char;//(char*)realloc(tmpbuf, sizeof(tmpbuf)+ j);
		} 
		if(vec.size()==3) {
			i=0;
			tmpbuf = new char;
			while(*ss!=0) {
			tmpbuf[i] = *ss;
			ss+=1;
			i++;
			}
		 
			vec.push_back(tmpbuf);
		}
		tmpbuf[i] = *ss;
	i++;
	}
	free(tmpbuf);
	return vec;
}

