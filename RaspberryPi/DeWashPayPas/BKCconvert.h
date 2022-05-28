#ifndef BKCCONVERT_H_
#define BKCCONVERT_H_

#include <iconv.h>  // convert encoding
#include <iostream>
#include <string.h>

void Utf(char* from, char* to, iconv_t d) {
	int rv = 0;
	size_t lf = 0, lt = 0;
	lf = strlen(from);
	lt = 2 * lf;
	rv = iconv(d, &from, &lf, &to, &lt);
    if (rv) {
		std::cout << "Encoding error: " << rv << std::endl;
    }
}


#endif /* BKCCONVERT_H_ */
