
#ifndef __NatureInfo_h__
#define __NatureInfo_h__

namespace Communication
{
	// enum NatureInfo;
}

namespace Communication
{
	enum NatureInfo
	{
		/**
		 * =1
		 */
		CL_TEMP = 1,
		CL_TEMPINCIDENT_MIN = 2,
		CL_TEMPINCIDENT_MAX = 3,
		CL_TEMP_DEFECTUEUX = 4,
		CL_TEMP_FININCIDENT = 255,
		CL_HUM = 1,
		CL_HUMINCIDENT_MIN = 2,
		CL_HUMINCIDENT_MAX = 3,
		CL_HUM_DEFECTUEUX = 4,
		CL_HUMNONINSTAL = 5,
		CL_HUM_FININCIDENT = 255,
		CL_QAIR = 1,
		CL_QAIRINCIDENT = 2,
		CL_QAIR_DEFECTUEUX = 3,
		CL_QAIRNONINSTAL = 5,
		CL_QAIR_FININCIDENT = 255,
		CL_PASDETRANSMISSION = 6
	};
}

#endif
