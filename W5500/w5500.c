#include "defines.h"
#include "w5500.h"

u_int localPort = 4000;

const u_char _socket_reg_block[8] = { 0x08, 0x28, 0x48, 0x68, 0x88, 0xA8, 0xC8, 0xE8 };
const u_char _socket_txb_block[8] = { 0x10, 0x30, 0x50, 0x70, 0x90, 0xB0, 0xD0, 0xF0 };
const u_char _socket_rxb_block[8] = { 0x18, 0x38, 0x58, 0x78, 0x98, 0xB8, 0xD8, 0xF8 };

extern u_char sendReceiveByteSPI(u_char byte);

/**
 * wait until socket closed status
 */
void waitUntilSocketClosed(u_char s) {
	while (getSn_SR(s) != SOCK_CLOSED)
		;
}

/**
 * open socket and wait for initiated status
 */
void openSocketOnPort(u_char s, u_char port) {
	socket(s, Sn_MR_TCP, port, 0x00);
	while (getSn_SR(s) != SOCK_INIT)
		;
}

/**
 * listen and wait for listening status
 */
void startListening(u_char s) {
	listen(s);
	while (getSn_SR(s) != SOCK_LISTEN)
		;
}

/**
 * establish connection for the channel in passive (server) mode.
 */
void listen(u_char s) {
	setSn_CR(s, Sn_CR_LISTEN);
	while (getSn_CR(s))
		;
}

/**
 * disconnect
 */
void disconnect(u_char s) {
	setSn_CR(s, Sn_CR_DISCON);
	while (getSn_CR(s))
		;
}

/**
 * close the socket
 */
void close(u_char s) {
	setSn_CR(s, Sn_CR_CLOSE);
	while (getSn_CR(s))
		;
	setSn_IR(s, 0xFF);
}

/**
 * initialize the channel in particular mode, set the port, and wait for W5500 to finish.
 */
void socket(u_char s, u_char protocol, u_int port, u_char flag) {
	setSn_MR(s, protocol | flag);
	if (port != 0) {
		setSn_PORT(s, port);
	} else {
		localPort++; // if not provided, set the source port number to an arbitrary number
		setSn_PORT(s, localPort);
	}
	setSn_CR(s, Sn_CR_OPEN);
	while (getSn_CR(s))
		;
}


// register read & write
u_char readRegisterByte(u_char offset, u_char control) {
	u_char byte = 0;
	wizSelect();;

	sendReceiveByteSPI(0);
	sendReceiveByteSPI(offset);
	sendReceiveByteSPI(control); // RWB_READ is 0, so we just skip it
	byte = sendReceiveByteSPI(0);

	wizDeselect();;
	return byte;
}
void writeRegisterByte(u_char offset, u_char control, u_char byte) {
	wizSelect();;

	sendReceiveByteSPI(0);
	sendReceiveByteSPI(offset);
	sendReceiveByteSPI(control | RWB_WRITE);
	sendReceiveByteSPI(byte);

	wizDeselect();;
}
u_int readRegisterWord(u_char offset, u_char control) {
	u_int word;
	wizSelect();;

	sendReceiveByteSPI(0);
	sendReceiveByteSPI(offset);
	sendReceiveByteSPI(control); // RWB_READ is 0, so we just skip it
	word = sendReceiveByteSPI(0);
	word <<= 8;
	word |= sendReceiveByteSPI(0);

	wizDeselect();;
	return word;
}
void writeRegisterWord(u_char offset, u_char control, u_int word) {
	wizSelect();;

	sendReceiveByteSPI(0);
	sendReceiveByteSPI(offset);
	sendReceiveByteSPI(control | RWB_WRITE);
	sendReceiveByteSPI(word >> 8);
	sendReceiveByteSPI(word);

	wizDeselect();;
}
void readRegisterArray(u_char offset, u_char control, u_char* array,
		u_char length) {
	u_char c;

	wizSelect();;

	sendReceiveByteSPI(0);
	sendReceiveByteSPI(offset);
	sendReceiveByteSPI(control); // RWB_READ is 0, so we just skip it
	for (c = 0; c < length; c++) {
		*array = sendReceiveByteSPI(0);
		array++;
	}

	wizDeselect();;
}
void writeRegisterArray(u_char offset, u_char control, u_char* array,
		u_char length) {
	u_char c;

	wizSelect();;

	sendReceiveByteSPI(0);
	sendReceiveByteSPI(offset);
	sendReceiveByteSPI(control | RWB_WRITE);
	for (c = 0; c < length; c++) {
		sendReceiveByteSPI(*array++);
	}

	wizDeselect();;
}
// memory read & write
u_char readMemoryByte(u_int addr, u_char control) {
	u_char byte;
	wizSelect();;

	sendReceiveByteSPI(addr >> 8);
	sendReceiveByteSPI(addr);
	sendReceiveByteSPI(control); // RWB_READ is 0, so we just skip it
	byte = sendReceiveByteSPI(0);

	wizDeselect();;
	return byte;
}
void writeMemoryByte(u_int addr, u_char control, u_char byte) {
	wizSelect();;

	sendReceiveByteSPI(addr >> 8);
	sendReceiveByteSPI(addr);
	sendReceiveByteSPI(control | RWB_WRITE);
	sendReceiveByteSPI(byte);

	wizDeselect();;
}
void readMemoryArray(u_int addr, u_char control, u_char* array, u_char length) {
	u_char c;

	wizSelect();;

	sendReceiveByteSPI(addr >> 8);
	sendReceiveByteSPI(addr);
	sendReceiveByteSPI(control); // RWB_READ is 0, so we just skip it
	for (c = 0; c < length; c++) {
		*array = sendReceiveByteSPI(0);
		array++;
	}

	wizDeselect();;
}
void writeMemoryArray(u_int addr, u_char control, u_char* array, u_char length) {
	u_char c;

	wizSelect();;

	sendReceiveByteSPI(addr >> 8);
	sendReceiveByteSPI(addr);
	sendReceiveByteSPI(control | RWB_WRITE);
	for (c = 0; c < length; c++) {
		sendReceiveByteSPI(*array++);
	}

	wizDeselect();;
}

void writeToTXBuffer(u_char s, u_char *array, u_char length) {
	u_int addr;
	if (length == 0) {
		return;
	}
	addr = getSn_TX_WR(s);
	writeMemoryArray(addr, _socket_txb_block[s], array, length);
	addr += length;
	setSn_TX_WR(s, addr);
}

void readFromRXBuffer(u_char s, u_char *array, u_char length) {
	u_int addr = 0;
	if (length == 0) {
		return;
	}
	addr = getSn_RX_RD(s);
	readMemoryArray(addr, _socket_rxb_block[s], array, length);
	addr += length;
	setSn_RX_RD(s, addr);
}


/**
 * copy local buffer to W5500 and send data
 */
u_int send(u_char s, const u_char * buffer, u_int * length, u_char retry) {
	u_char status = 0; // TODO define statuses
	u_int txPointerBefore, txPointerAfter;

	if (!retry) {
		do {
			status = getSn_SR(s);
			if ((status != SOCK_ESTABLISHED) && (status != SOCK_CLOSE_WAIT)) {
				return 2;
			}
		} while (getTXFreeSize(s) < *length);

		writeToTXBuffer(s, (u_char *) buffer, *length);
	}

	txPointerBefore = getSn_TX_RD(s);

	setSn_CR(s, Sn_CR_SEND);
	while (getSn_CR(s))
		;

	while ((getSn_IR(s) & Sn_IR_SEND_OK) != Sn_IR_SEND_OK) {
		if (getSn_IR(s) == SOCK_CLOSED) {
			close(s);
			return 3;
		}
	}
	setSn_IR(s, Sn_IR_SEND_OK); // wasn't SEND_OK set already internally?

	txPointerAfter = getSn_TX_RD(s);

	*length = txPointerAfter - txPointerBefore;
	if (txPointerAfter > txPointerBefore) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * copy received data from W5500's RX buffer to the local buffer
 */
void receive(u_char s, u_char * buffer, u_int length) {
	readFromRXBuffer(s, buffer, length);
	setSn_CR(s, Sn_CR_RECV);
	while (getSn_CR(s))
		;
}

void clearBuffer(u_char* array, u_char length) {
	while ( length != 0) {
		*array++ = 0;
		length--;
	}
}

u_int getTXFreeSize(u_char s) {
	u_int firstRead = 0, secondRead = 0;
	do {
		secondRead = getSn_TX_FSR(s);
		if (secondRead != 0) {
			firstRead = getSn_TX_FSR(s);
		}
	} while (firstRead != secondRead);
	return firstRead;
}

u_int getRXReceived(u_char s) {
	u_int firstRead = 0, secondRead = 0;
	do {
		secondRead = getSn_RX_RSR(s);
		if (secondRead != 0) {
			firstRead = getSn_RX_RSR(s);
		}
	} while (firstRead != secondRead);
	return firstRead;
}

