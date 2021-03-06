#include <Box2D/Box2D.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <exception>
#include <stdio.h>
#include <cstdio>
//REMEMBER TO EDIT Linker -> System -> SubSystem -> WINDOW to hide console!

//This program currently just move a green block on a black background. I'm using this to learn and test aspects

const float FPS = 60;
const int BOUNCER_SIZE = 32;
const int scrn_W = 1024;
const int scrn_H = 700;
int bulletCount = 5;
const int NUM_BULLETS = 5;
int pos_x = scrn_W / 2;
int pos_y = scrn_H / 2;

static ALLEGRO_COLOR red,blue,black,white,green;
enum KEYS{ UP, DOWN, LEFT, RIGHT };


int main(void)
{
	//int pos_x = scrn_W / 2;
	//int pos_y = scrn_H / 2;
	float bouncer_x = scrn_W / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_y = scrn_H / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_dx = -4.0, bouncer_dy = 4.0;
	bool done = false, fired = false;
	bool keys[4] = { false, false, false, false };

	//Character variables
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 20;
	int frameW = 128;
	int frameH = 128;
	const int maxFrame = 4;


	//Bullets

	//end bullets

	//End character variables

	//Initialisers
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *walkLeft, *walkRight,*standLeft, *standRight,*select;


	if (!al_init())											//initialize and check Allegro
	{
		al_show_native_message_box(display, "Error!", "Warning!", "Failed to initialise Allegro! \n Closing Application!", NULL, ALLEGRO_MESSAGEBOX_WARN);
		//fprintf(stderr, "failed to initialize allegro!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	display = al_create_display(scrn_W, scrn_H);			//create our display object
	if (!display)											//Check display
	{
		al_show_native_message_box(display, "Error!", "Warning!", "Failed to initialise display! \n Closing Application!", NULL, ALLEGRO_MESSAGEBOX_WARN);
		//fprintf(stderr, "failed to create display!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);		//create box 
	if (!bouncer) {												//Check creation of box 
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);							//Create Timer
	if (!timer)													//Check timer creation
	{				
		al_show_native_message_box(display, "Error!", "Warning!", "Failed to initialise timer! \n Closing Application!", NULL, ALLEGRO_MESSAGEBOX_WARN);
		//fprintf(stderr, "failed to create timer!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	event_queue = al_create_event_queue();						//Create event queue
	if (!event_queue)											//Check event queue creation
	{											
		al_show_native_message_box(display, "Error!", "Warning!", "Failed to initialise event queue! \n Closing Application!", NULL, ALLEGRO_MESSAGEBOX_WARN);
		//fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}


	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();


	//Init animated character
	al_init_image_addon();
	//Init bitmap

	walkRight = al_load_bitmap("./images/kriWalkR.png");
	walkLeft = al_load_bitmap("./images/kriWalkL.png");
	standLeft = al_load_bitmap("./images/kriL.png");
	standRight = al_load_bitmap("./images/kriR.png");
	select = standRight;
	int direction = 1;

   // al_convert_mask_to_alpha(walkLeft, al_map_rgb(106, 76, 48));
	//al_convert_mask_to_alpha(select, al_map_rgb(106, 76, 48));
	//al_convert_mask_to_alpha(walkRight, al_map_rgb(106, 76, 48));


	//end animated character

	//Event queue - register listeners
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//end event queue

	//Colours
	black = al_map_rgb(0,0,0);
	white = al_map_rgb(255, 255, 255);
	red = al_map_rgb(255, 0, 0);
	green = al_map_rgb(0, 255, 0);
	blue = al_map_rgb(0, 0, 255);
	//End Colours

	//End initialisers

	al_start_timer(timer);
	al_set_target_bitmap(bouncer);
	al_clear_to_color(black);
	al_set_target_bitmap(al_get_backbuffer(display));
	//al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, green);
	al_flip_display();
	
	
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			static bool fired = false;
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				if (direction == 1) select = walkRight;
				else select = walkLeft;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				if (direction == 1) select = walkRight;
				else select = walkLeft;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				if (direction == 1) select = walkRight;
				else select = walkLeft;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
				if (direction == 1) select = walkRight;
				else select = walkLeft;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				select = walkRight;
				direction = 1;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				select = walkRight;
				direction = 1;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				select = walkLeft;
				direction = 0;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				select = walkLeft;
				direction = 0;
				break;
			case ALLEGRO_KEY_SPACE:

				break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				if (direction == 1) select = standRight;
				else select = standLeft;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = false;
				if (direction == 1) select = standRight;
				else select = standLeft;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				if (direction == 1) select = standRight;
				else select = standLeft;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
				if (direction == 1) select = standRight;
				else select = standLeft;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				select = standRight;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
				select = standRight;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				select = standLeft;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
				select = standLeft;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (++frameCount >= frameDelay)
			{
				if (++curFrame >= maxFrame)
				{
					curFrame = 0;
				}
				frameCount = 0;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		pos_y -= keys[UP] * 10;
		pos_y += keys[DOWN] * 10;
		pos_x -= keys[LEFT] * 10;
		pos_x += keys[RIGHT] * 10;





		//al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, green);
		al_draw_scaled_bitmap(select, curFrame*frameW, 0, 128, 128, pos_x, pos_y, 300, 300, 0);    //makes shit big
		//al_draw_bitmap_region(select, curFrame * frameW, 0, frameW, frameH,pos_x,pos_y,0);
		//wal_draw_bitmap(select, pos_x, pos_y, 0);
		al_flip_display();
		al_clear_to_color(black);
	}

	//Destruction

	al_destroy_bitmap(walkLeft);
	al_destroy_bitmap(walkRight);
	//al_destroy_bitmap(select);
	//al_destroy_bitmap(stand);
	al_destroy_bitmap(bouncer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	//end Distruction
	return 0;
}





