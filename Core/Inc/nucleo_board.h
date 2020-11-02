/*
 * Nucleoboard.h
 *
 *  Created on: Nov 1, 2020
 *      Author: joaquin.alvidrez
 */

#ifndef NUCLEOBOARD_H_
#define NUCLEOBOARD_H_

class Nucleo_board {
public:
	Nucleo_board();
	virtual ~Nucleo_board();
	static void init_led();
};


#endif /* NUCLEOBOARD_H_ */
