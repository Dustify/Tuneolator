// #include "control.h"
//
// class Demo {
// public:
// static void cycleNotes() {
// 	for (int i = 0; i < 128; i++) {
// 		Control::playNote(i, 1);
// 	}
//
// 	for (int i = 126; i > 0; i--) {
// 		Control::playNote(i, 1);
// 	}
// }
//
// static void vangelis() {
// 	Control::playNote(67, 2);
// 	Control::playNote(69, 2);
// 	Control::playNote(64, 2);
// 	Control::playNote(62, 4);
// 	Control::pause(2);
//
// 	Control::playNote(67, 3);
// 	Control::playNote(69, 1);
// 	Control::playNote(72, 4);
// 	Control::pause(2);
//
// 	Control::playNote(71, 0.5);
// 	Control::playNote(69, 0.5);
// 	Control::playNote(71, 4);
// }
//
// static void numan() {
// 	Control::playNote(72, 1);
// 	Control::playNote(71, 1);
// 	Control::playNote(65, 1);
// 	Control::playNote(67, 1);
// 	Control::pause(1);
// 	Control::playNote(67, 0.5);
// 	Control::pause(0.5);
// 	Control::playNote(67, 1);
// 	Control::pause(1);
//
// 	Control::playNote(72, 1);
// 	Control::playNote(71, 1);
// 	Control::playNote(65, 1);
// 	Control::playNote(67, 1);
// 	Control::pause(1);
// 	Control::playNote(67, 0.5);
// 	Control::pause(0.5);
// 	Control::playNote(67, 1);
// 	Control::pause(1);
//
// 	Control::playNote(72, 1);
// 	Control::playNote(71, 1);
// 	Control::playNote(65, 1);
// 	Control::playNote(67, 1);
// 	Control::pause(1);
// 	Control::playNote(67, 0.5);
// 	Control::pause(0.5);
// 	Control::playNote(67, 1);
// 	Control::pause(1);
//
// 	Control::playNote(72, 1);
// 	Control::playNote(71, 1);
// 	Control::playNote(65, 1);
// 	Control::playNote(67, 1);
// 	Control::pause(1);
// 	Control::playNote(67, 0.5);
// 	Control::pause(0.5);
// 	Control::playNote(67, 1);
//
// 	Control::playNote(64, 1);
// 	Control::playNote(65, 1);
// 	Control::pause(0.75);
// 	Control::playNote(69, 1);
// 	Control::playNote(65, 1);
// 	Control::pause(2);
//
// 	Control::playNote(64, 1);
// 	Control::playNote(65, 0.9);
// 	Control::pause(0.1);
// 	Control::playNote(65, 0.9);
// 	Control::playNote(69, 1);
// 	Control::playNote(65, 1);
// }
//
// static void cycleTunes() {
// 	vangelis();
// 	Control::pause(8);
// 	numan();
// 	Control::pause(8);
// }
// };
