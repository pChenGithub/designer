
#include "producers/quzhou.h"
#include "sensorsManager.h"
#include "object.h"
#include "producersManager.h"

void quzhou_pro_init(struct producer* pro) {
	struct runTime_object* obj = & (pro->pm->rt->object);
	struct sensorsManager* sm = obj->sm;
	struct sensor* sensor;

	sensor = SENSOR_INIT(pt100);
	sm->add_sensor(sm, sensor);
	sensor = SENSOR_INIT(press303);
	sm->add_sensor(sm, sensor);

}

