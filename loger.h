/**********************************************************************************************//**
 * \file	loger.h.
 *
 * \brief	Declares the loger class
 **************************************************************************************************/

#ifndef LOGER_H
#define LOGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QDebug>
#include <QDir>
#include "utility.h"

 /**********************************************************************************************//**
  * \class	Loger
  *
  * \brief	A loger.
  *
  * \author	Hmm
  * \date	2017/10/27
  **************************************************************************************************/

class Loger : public QObject
{
	Q_OBJECT

public:

	/**********************************************************************************************//**
	 * \fn	Loger::~Loger();
	 *
	 * \brief	Destructor
	 *
	 * \author	Hmm
	 * \date	2017/10/27
	 **************************************************************************************************/

	~Loger();

	/**********************************************************************************************//**
	 * \fn	static Loger * Loger::getInstance();
	 *
	 * \brief	Gets the instance
	 *
	 * \author	Hmm
	 * \date	2017/10/27
	 *
	 * \return	Null if it fails, else the instance.
	 **************************************************************************************************/

	static Loger * getInstance();

	/**********************************************************************************************//**
	 * \fn	void Loger::writeLog(QString log);
	 *
	 * \brief	Writes a log
	 *
	 * \author	Hmm
	 * \date	2017/10/27
	 *
	 * \param	log	The log.
	 **************************************************************************************************/

	void writeLog(QString log);

	/**********************************************************************************************//**
	 * \fn	void Loger::updateLogFileName();
	 *
	 * \brief	Updates the log file name
	 *
	 * \author	Hmm
	 * \date	2017/10/27
	 **************************************************************************************************/

	void updateLogFileName();
private:

	/**********************************************************************************************//**
	 * \fn	Loger::Loger(QObject *parent);
	 *
	 * \brief	Constructor
	 *
	 * \author	Hmm
	 * \date	2017/10/27
	 *
	 * \param [in,out]	parent	If non-null, the parent.
	 **************************************************************************************************/

	Loger(QObject *parent);

	/**********************************************************************************************//**
	 * \fn	void Loger::removeDepressedLogFiles();
	 *
	 * \brief	Removes the depressed log files
	 *
	 * \author	Hmm
	 * \date	2017/10/27
	 **************************************************************************************************/

	void removeDepressedLogFiles();
private:
	/** \brief	The file */
	QFile *m_file;
	/** \brief	The ts */
	QTextStream *m_ts;
};

#endif // LOGER_H
