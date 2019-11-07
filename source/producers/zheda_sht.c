
#include "producers/zheda_sht.h"
#include "sensorsManager.h"
#include "object.h"
#include "producersManager.h"

void zheda_sht_pro_init(struct producer* pro) {
	struct runTime_object* obj = & (pro->pm->rt->object);
	struct sensorsManager* sm = obj->sm;
	struct sensor* sensor;

	sensor = SENSOR_INIT(sht20_t);
	sm->add_sensor(sm, sensor);
	sensor = SENSOR_INIT(sht20_h);
	sm->add_sensor(sm, sensor);

}

