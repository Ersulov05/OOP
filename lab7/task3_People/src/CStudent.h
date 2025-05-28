#pragma once
#include "./CStudentImpl.h"
#include "./IStudent.h"
#include <string>

class CStudent : public CStudentImpl<IStudent>
{
public:
	CStudent(
		const std::string& firstName,
		const std::string& secondName,
		const std::string& thirdName,
		const std::string& addres,
		const std::string& universityName,
		const std::string& studentTicketNumber)
		: CStudentImpl<IStudent>(
			  firstName,
			  secondName,
			  thirdName,
			  addres,
			  universityName,
			  studentTicketNumber){};
};