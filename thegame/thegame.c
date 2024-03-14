#include"common.h"
#include"MAIN.h"
void do_menuevent();
void draw_menu();


int main(int argc,char*argv[])//主程序内装各种封装的函数
{

	init_app();


	Prepare_All();

	draw_menu();
	do_menuevent();

	




	quit_app();//destroy和free包含在quit函数中
	
}

static void init_app()
{

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		HANDLE_ERROR("init video");

	}
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
		HANDLE_ERROR("init image");
	}
	if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC)) {
		HANDLE_ERROR("init mixer");
	}
	if (TTF_Init() == -1) {
		HANDLE_ERROR("init ttf");
	}




}

static void quit_app()
{
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(app.render);
	SDL_DestroyWindow(app.Window);

	SDL_FreeSurface(app.surface_road);
	SDL_FreeSurface(app.surface_menu);


	SDL_DestroyTexture(app.texture_road);
	SDL_DestroyTexture(app.texture_title);
	SDL_DestroyTexture(app.texture_menu);
	TTF_CloseFont(app.font_title);
	
	return 0;
}

void Prepare_All() {

	app.Window = SDL_CreateWindow("the flight of yjsp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width_Window, Height_Window, SDL_WINDOW_SHOWN);//创建窗口
	app.render = SDL_CreateRenderer(app.Window, -1, SDL_RENDERER_ACCELERATED);//创建渲染器

	app.surface_road = IMG_Load("images/shimoki.jpg");//load图片必须用英文 road section
	app.texture_road = SDL_CreateTextureFromSurface(app.render, app.surface_road);
	SDL_RenderCopy(app.render, app.texture_road, NULL, NULL);//后面两个是矩形参数 
	
	app.font_title = TTF_OpenFont("fonts/Ankh.ttf", 36);
	SDL_Color color_title = { .r = 0,.g = 0,.b = 0,.a = 0 };
	app.surface_title = TTF_RenderText_Blended(app.font_title, "press space to start", color_title);
	app.texture_title = SDL_CreateTextureFromSurface(app.render, app.surface_title);
	app.rect_title.x = 95;
	app.rect_title.y = 5;
	app.rect_title.w = 500;
	app.rect_title.h = 500;
	SDL_QueryTexture(app.texture_title, NULL, NULL, &app.rect_title.w, &app.rect_title.h);



	app.Road_rect[0].x = 0;
	app.Road_rect[0].y = 0;
	app.Road_rect[0].w = app.surface_road->w;
	app.Road_rect[0].h = app.surface_road->h;

	app.Road_rect[1].x = app.surface_road->w;
	app.Road_rect[1].y = 0;
	app.Road_rect[1].w = app.surface_road->w;
	app.Road_rect[1].h = app.surface_road->h;

}

void Render_Background() {


	for (int i = 0; i < 2; i++)
	{
		app.Road_rect[i].x -= V;
		if (app.Road_rect[i].x < -app.surface_road->w)
		{
			app.Road_rect[i].x += app.surface_road->w * 2;//将矩形提到右侧开头处
		}
		
	}
	for (int i = 0; i < 2; i++) {
		SDL_RenderCopy(app.render, app.texture_road, NULL, &app.Road_rect[i]);//复制到渲染器
	}

}


void do_menuevent() {//菜单界面的事件处理

	while (SDL_WaitEvent(&app.mainevent)) {
		switch (app.mainevent.type) {
			case SDL_QUIT:
				quit_app();
				break;
			case SDL_KEYDOWN:
				switch (app.mainevent.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit_app();
					break;
				case SDLK_SPACE:

					SDL_RenderClear(app.render);
					play();
					quit_app();
					break;
				default:
					break;

				}
				break;

			default:
				break;
		}
		


	}


}

void draw_menu() {
	app.surface_menu = IMG_Load("images/yjsp.png");//load图片必须用英文
	app.texture_menu = SDL_CreateTextureFromSurface(app.render, app.surface_menu);
	SDL_RenderCopy(app.render, app.texture_menu, NULL, NULL);//后面两个是矩形参数 
	SDL_RenderCopy(app.render, app.texture_title, NULL, &app.rect_title);
	SDL_RenderPresent(app.render);
}

void playset()
{
	srand((unsigned int)time(NULL));
	jump = false;
	down = false;
	crouch = false;
	collision = false;
	score_m = 0;
}
void play() {
	playset();
	while (true) {


		clock_t FstartTime = clock();
		if (SDL_PollEvent(&app.event))
		{
			switch (app.event.type)
			{
			case SDL_QUIT:
				return;
				break;
			case SDL_KEYDOWN:
				switch (app.event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					return;
					break;
				case SDLK_DOWN:
					down = true;
					break;
				case SDLK_UP:
				case SDLK_SPACE:
					jump = true;
					break;
				default:
					break;
				}
				break;

			case SDL_KEYUP:
				switch (app.event.key.keysym.sym)
				{
				case SDLK_DOWN:
					down = false;
					crouch = false;
					break;//将俯冲状态解除
				default:
					break;
				}
				break;
			default:
				break;
			}
			
			
		}

		score_m++;//根据分数加速
		if (score_m >= 2500)
		{
			rate = 1.25;
		}
		else if(score_m>10000)
		{
			rate = 1.5;

		}
		SDL_RenderClear(app.render);

		Render_Background();

		SDL_RenderPresent(app.render);
		SDL_Delay(10);

	}
}


