#include "Debris.hpp"

//CONSTUCTOR
/*Creates a new piece of debris, takes a texture, the x and y positions,
the number of debris the logo is wide and high, the index of this debris in relation
to the logo height and width, and the point of force x and y*/
Debris::Debris(GLuint t, float x, float y, float wc, float hc, float i, float j, float fx, float fy, int m) {
	mode = m;
	tex= t;
	xPos = orgX = x;
	yPos = orgY = y;
	fX = fx;
	fY = fy;
	
	//find the texture coordinates
	tX1 = i/wc;
	tX2 = (i+1)/wc;
	tY1 = j/hc;
	tY2 = (j+1)/hc;

	int maxDis = 900; //the max distance the blast can be away before it doesn't affect the debris

	//find the distance this is from the epicentre of the force
	float distance = sqrt(pow((x-fx), 2)+pow((y-fy), 2));

	float power = 1-(distance/maxDis); //the power of the blast affecting this

	if (power > 0) {
		speed = MAX_SPEED*power;
		speed += (rand()%2)+1;
		direction = -1*(atan2(y-fy, x-fx)*(180.0f/PI)-90);
		direction += (rand()%20)-10;
		rotationSpeed = (fx-x)/100+(fy-y)/100;
	}
	else {
		speed = 0;
		direction = 90;
		rotationSpeed = 0;
	}

	orgSpeed = speed;

	//rotation always starts at 0
	rotation = 0;

	//mode settings
	pullIn = true;
	takeOff = false;
	flap = 0;
	if (mode == BUTTERFLY) {
		speed /= 2; //half speed
	}
	reform = false;
	fall = false;
}

//DESTRUCTOR
Debris::~Debris() {}

//FUNCTIONS
/*Update the debris*/
void Debris::update() {
	if (mode == BLACKHOLE) speed -= GRAVITY; //pull towards/away from the centre
	else if (mode == BUTTERFLY) {
		if (takeOff && rand()%3 == 1) { //1 in 3 chance to change direction
			direction = rand()%360+1;
			flap += 90;
		}
	}
	else if (mode == REFORM) {
		if (!reform) {
			if (speed > 0) speed -= GRAVITY; //slow down
			else {
				reform = true;
				speed = 0; //stop
				direction = -1*(atan2(yPos-orgY, xPos-orgX)*(180.0f/PI)-90); //reverse the direction
			}
		}
		else { //move back to original point
			if (xPos > orgX-DEBRIS_WIDTH*8 && xPos < orgX+DEBRIS_WIDTH*8 && yPos > orgY-DEBRIS_WIDTH*8 && yPos < orgY+DEBRIS_WIDTH*8) {
				xPos = orgX;
				yPos = orgY;
				speed = 0;
			}
			else if (speed < 8) speed -= GRAVITY; //speed up
		}
		if (rotationSpeed > 0) rotationSpeed -= GRAVITY;//slow down rotation
		else {
			rotationSpeed = 0;
			rotation = 0;
		}
	}
	else if (mode == SWISH) {
		if (!fall) {
			if (speed > 0) speed -= GRAVITY; //slow down
			else {
				speed = 8;
				fall = true;
				direction = -direction;
			}
		}
		else {
			if (speed > -8) speed -= GRAVITY;
		}
	}

	//move and rotate
	if (mode == BUTTERFLY && !takeOff) {
		if (rand()%100 == 1) takeOff = true; //1 in 20 chace it will take off
	}
	else {
		xPos += speed*sin(direction*PI/180.0f);
		yPos += speed*cos(direction*PI/180.0f);
		rotation += rotationSpeed;
	}
}

/*Draw the debris*/
void Debris::draw() {
	glBindTexture(GL_TEXTURE_2D, tex);

	glPushMatrix();

	//translate
	glTranslatef(xPos+DEBRIS_WIDTH/2, yPos+DEBRIS_WIDTH/2, 0);

	//rotate
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glRotatef(flap, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(tX1, tY1); glVertex2f(-DEBRIS_WIDTH/2, -DEBRIS_WIDTH/2);
	glTexCoord2f(tX2, tY1); glVertex2f(DEBRIS_WIDTH/2,  -DEBRIS_WIDTH/2);
	glTexCoord2f(tX2, tY2); glVertex2f(DEBRIS_WIDTH/2,  DEBRIS_WIDTH/2);
	glTexCoord2f(tX1, tY2); glVertex2f(-DEBRIS_WIDTH/2, DEBRIS_WIDTH/2);
	glEnd();


	glPopMatrix();
}