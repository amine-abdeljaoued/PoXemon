
#include "Player.h"

template <typename T>
//will be used for either player or opponent

void fall(T& eevee, float& groundY, float &deltaTime) {//make player fall if it is still in the air
	if (eevee.y < groundY) {

		eevee.velocityY += 981.0f * deltaTime;
		eevee.y += eevee.velocityY * deltaTime;
		eevee.sprite.setPosition(eevee.x, eevee.y);

		if (eevee.y >= groundY) {
			eevee.y = groundY;
			eevee.velocityY = 0.0f;
		}

	}
}







