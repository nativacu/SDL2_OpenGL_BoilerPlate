#include "game.hpp"

game::game::game()
{
}

game::game::game(int width, int height)
{

	mWidth = width;
	mHeight = height;
	mRenderer = engine::renderer::renderer(mWidth, mHeight);

	mTestBlock.get_model_matrix()->translate_matrix(mTestBlock.get_component("position")->get_position());
	mTestBlock.get_model_matrix()->rotate_using_radians(0.0f);
	mTestBlock.get_model_matrix()->scale_matrix(1.0f, 1.0f, 1.0f);

	mBall.get_model_matrix()->translate_matrix(mBall.get_component("position")->get_position());
	mBall.get_model_matrix()->rotate_using_radians(0.0f);
	mBall.get_model_matrix()->scale_matrix(1.0f, 1.0f, 1.0f);

	mPaddle.get_model_matrix()->translate_matrix(mPaddle.get_component("position")->get_position());
	mPaddle.get_model_matrix()->rotate_using_radians(0.0f);
	mPaddle.get_model_matrix()->scale_matrix(1.0f, 1.0f, 1.0f);

	mSoundEngine = irrklang::createIrrKlangDevice();
}

void game::game::execute(void)
{
	mBlocks = mLevel.mBlocks;
	mRenderer.get_program_ID();
	mLevel.load("levels/lvl_1.txt", 3.12, 0.9);
	for (int i = 0; i < mBlocks.size(); i++) {
		mBlocks[i]->get_model_matrix()->translate_matrix(mBlocks[i]->get_component("position")->get_position());
		mBlocks[i]->get_model_matrix()->rotate_using_radians(0.0f);
		mBlocks[i]->get_model_matrix()->scale_matrix(1.0f, 1.0f, 1.0f);
	}
}

void game::game::update(void)
{
	engine::math::mathUtilities utility;
	respond_to_input();
	if (mBall.get_status()) {
		engine::math::vector4 currentBallPosition = mBall.get_component("position")->get_position();
		
		if (currentBallPosition.y < 3.6f && !mBall.get_is_going_down()) {
			mBall.get_model_matrix()->translate_matrix(engine::math::vector4(0.0f, 0.02f, 0.0f, 0.0f));
			currentBallPosition.y += 0.05f;
		}
		else {
			mBall.set_is_going_down(true);
			mBall.get_model_matrix()->translate_matrix(engine::math::vector4(0.0f, -0.02f, 0.0f, 0.0f));
			currentBallPosition.y -= 0.05f;
		}
		mBall.get_component("position")->set_position(currentBallPosition);
	}

	/*engine::math::vector4 currentBallPosition = mBall.get_component("position")->get_position();
	// If not stuck to player board
	if (mBall.get_status())
	{
		// Move the ball
		currentBallPosition.x -= (0.02f * std::sinf(utility.to_radians(45)));
		currentBallPosition.y += (0.02f * std::cosf(utility.to_radians(45)));

		//mBall.get_model_matrix()->identity();
		mBall.get_model_matrix()->translate_matrix(currentBallPosition);
		mBall.get_model_matrix()->rotate_z(0.0f);
		mBall.get_model_matrix()->scale_matrix(1.0f, 1.0f, 1.0f);
	}*/

}

void game::game::render(void)
{
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT );

	for (int i = 0; i < mBlocks.size(); i++) {
		mRenderer.render_object(*mLevel.mBlocks[i]);
	}

	mRenderer.render_object(mTestBlock);
	mRenderer.render_object(mBall);
	mRenderer.render_object(mPaddle);
	//mBackground.render();
}

void game::game::clean_up()
{
	mRenderer.clean_up();
}

void game::game::respond_to_input()
{

	if (mInputManager.get_w_key_status())	{
		mRenderer.toggle_wire_frame_view(true);
	}

	if (!mInputManager.get_w_key_status()){
		mRenderer.toggle_wire_frame_view(false);
	}

	if (mInputManager.get_a_key_status())
	{
		engine::math::vector4 currentPaddlePosition = mPaddle.get_component("position")->get_position();
		engine::math::vector4 currentBallPosition = mBall.get_component("position")->get_position();
		if (currentPaddlePosition.x >= -1 + 0.18f)
		{
			mPaddle.get_model_matrix()->translate_matrix(engine::math::vector4(-0.02f, 0.0f, 0.0f, 0.0f));
			currentPaddlePosition.x -= 0.02f;
			mPaddle.get_component("position")->set_position(currentPaddlePosition);
			
			if (!mBall.get_status()) {
				mBall.get_model_matrix()->translate_matrix(engine::math::vector4(-0.02f, 0.0f, 0.0f, 0.0f));
				currentBallPosition.x -= 0.02f;
				mBall.get_component("position")->set_position(currentBallPosition);
			}
		}
	}

	if (mInputManager.get_d_key_status())
	{
		engine::math::vector4 currentPaddlePosition = mPaddle.get_component("position")->get_position();
		engine::math::vector4 currentBallPosition = mBall.get_component("position")->get_position();
		if (currentPaddlePosition.x <= 1 - 0.18f)
		{
			mPaddle.get_model_matrix()->translate_matrix(engine::math::vector4(0.02f, 0.0f, 0.0f, 0.0f));
			currentPaddlePosition.x += 0.02f;
			mPaddle.get_component("position")->set_position(currentPaddlePosition);
		
			if (!mBall.get_status()) {
				mBall.get_model_matrix()->translate_matrix(engine::math::vector4(0.02f, 0.0f, 0.0f, 0.0f));
				currentBallPosition.x += 0.02f;
				mBall.get_component("position")->set_position(currentBallPosition);
			}
		}
	}

	if (mInputManager.get_space_key_status()) {
		mSoundEngine->play2D("sounds/bangLarge.wav"); //sound
		mBall.release_ball();
	}
}

void game::game::set_input(char pInput)
{
	if (pInput == 'w') 
	{
		mInputManager.set_w_key_pressed_status(true);
	}

	else if (pInput == 'a') 
	{
		mInputManager.set_a_key_pressed_status(true);
	}

	else if (pInput == 'd')
	{
		mInputManager.set_d_key_pressed_status(true);
	}

	else if (pInput == 's') {
		mInputManager.set_space_key_pressed_status(true);
	}

	else{
		mInputManager.set_w_key_pressed_status(false);
		mInputManager.set_a_key_pressed_status(false);
		mInputManager.set_d_key_pressed_status(false);
		mInputManager.set_space_key_pressed_status(false);
	}
}
