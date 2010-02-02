/** $Id: double_controller.h 1182 2010-01-25 22:08:36Z mhauer $
	Copyright (C) 2010 Battelle Memorial Institute
	@file double_controller.h
	@addtogroup double_controller
	@ingroup market

 **/

#ifndef _MARKET_DOUBLE_CONTROLLER
#define _MARKET_DOUBLE_CONTROLLER

#include <stdarg.h>
#include "auction.h"
#include "gridlabd.h"

class double_controller
{
public:
	double_controller(MODULE *);
	int create();
	int init(OBJECT *parent);
	TIMESTAMP presync(TIMESTAMP t0, TIMESTAMP t1);
	TIMESTAMP sync(TIMESTAMP t0, TIMESTAMP t1);
	TIMESTAMP postsync(TIMESTAMP t0, TIMESTAMP t1);
	static CLASS *oclass;
public:
	typedef enum{
		ST_NONE=0,
		ST_HOUSE=1,
		//ST_OFFICE=2,
	} SETUPMODE;
	SETUPMODE setup_mode;

	typedef enum{
		TM_INVALID=0,
		TM_OFF=1,
		TM_HEAT=2,
		TM_COOL=3,
	} THERMOSTATMODE;
	THERMOSTATMODE thermostat_mode, last_mode;

	typedef enum{
		RM_NONE=0,
		RM_DEADBAND=1,
		RM_STICKY=2,
	} RESOLVEMODE;
	RESOLVEMODE resolve_mode;

	typedef enum{
		BM_OFF=0,
		BM_ON=1,
	} BIDMODE;
	BIDMODE bid_mode;

	int64 last_mode_timer;
	double cool_ramp_low,	heat_ramp_low;
	double cool_ramp_high,	heat_ramp_high;
	double cool_range_low,	heat_range_low;
	double cool_range_high,	heat_range_high;
	double cool_temp_min,	heat_temp_min;
	double cool_temp_max,	heat_temp_max;
	double cool_set_base,	heat_set_base;
	double cool_setpoint,	heat_setpoint;

	double cool_bid,	heat_bid;
	double cool_demand,	heat_demand;

	double temperature;
	double deadband;
	double load;
	double total;

	char32 temperature_name;
	char32 deadband_name;
	char32 cool_setpoint_name,	heat_setpoint_name;
	char32 cool_demand_name,	heat_demand_name;
	char32 state_name;
	char32 load_name;
	char32 total_load_name;

	//auction *market;
	OBJECT *pMarket;
	int32 lastbid_id;
	int64 lastmkt_id;
	double last_price,	bid_price;
	double last_quant,	bid_quant;
	double market_period;
	double avg_price;
private:
	void cheat();
	void fetch(double **value, char *name, OBJECT *parent, PROPERTY **prop, char *goal);

	TIMESTAMP next_run;

	PROPERTY *temperature_prop;
	PROPERTY *cool_setpoint_prop, *heat_setpoint_prop;
	PROPERTY *cool_demand_prop, *heat_demand_prop;
	PROPERTY *load_prop;
	PROPERTY *total_load_prop;
	
	double *cool_setpoint_ptr,	*heat_setpoint_ptr;
	double *cool_demand_ptr,	*heat_demand_ptr;
	double *temperature_ptr;
	double *load_ptr;
	double *total_load_ptr;
	enumeration *state_ptr;

	double cool_limit, heat_limit;
	double *pAvg24, *pStd24;
	double *pPeriod;
	double *pNextP;
	int64 *pMarketID;
};

#endif

// EOF
