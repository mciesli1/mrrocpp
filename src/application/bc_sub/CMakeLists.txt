add_executable(ecp_bcmain
	ecp_t_bcmain.cc
	ecp_st_servomove.cc
	ecp_st_codescan.cc
    ../servovision/ib_eih_visual_servo.cc
    ../servovision/visual_servo.cc
    ../servovision/visual_servo_manager.cc
    ../servovision/single_visual_servo_manager.cc
    ../servovision/position_constraint.cc
    ../servovision/cubic_constraint.cc
    ../servovision/object_reached_termination_condition.cc
    ../servovision/termination_condition.cc
)

target_link_libraries(ecp_bcmain ecp)


add_executable(mp_cashier
	mp_t_cashier.cc
)

target_link_libraries(mp_cashier mp)

install(TARGETS ecp_bcmain mp_cashier DESTINATION bin)