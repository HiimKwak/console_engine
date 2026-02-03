#include "Renderer.h"
#include "ScreenBuffer.h"
#include "Util/Util.h"

namespace Wanted
{
	Renderer::Frame::Frame(int bufferCount)
	{
		charInfoArray = new CHAR_INFO[bufferCount];
		memset(charInfoArray, 0, sizeof(CHAR_INFO) * bufferCount);
		//ZeroMemory(charInfoArray, sizeof(CHAR_INFO) * bufferCount) macro, 결국은 memset 호출

		sortingOrderArray = new int[bufferCount];
		memset(sortingOrderArray, 0, sizeof(int) * bufferCount); // 배열 동적할당 후엔 memset으로 제대로 초기화해주는게 좋음
	}
	Renderer::Frame::~Frame()
	{
		SafeDeleteArray(charInfoArray);
		SafeDeleteArray(sortingOrderArray);
	}
	void Renderer::Frame::Clear(const Vector2& screenSize)
	{
		// 2차원 배열로 다루는 1차원 배열을 순회하면서
		// 빈 문자(' ')로 설정
		const int width = screenSize.x;
		const int height = screenSize.y;

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < height; ++x)
			{
				// 2차원 배열처럼 사용하는 1차원 배열에서 인덱스 구하기
				const int index = (y * width) + x;

				// 글자 값 및 속성 설정
				CHAR_INFO& info = charInfoArray[index];
				info.Char.AsciiChar = ' ';
				info.Attributes = 0;

				// 그리기 우선순위 초기화
				sortingOrderArray[index] = -1;
			}
		}
	}

	// ----------- Frame ------------------- //
	// 정적 변수 초기화
	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer(const Vector2& screenSize)
		: screenSize(screenSize)
	{
		instance = this;

		const int bufferCount = screenSize.x * screenSize.y;
		frame = new Frame(bufferCount);

		// 프레임 초기화
		frame->Clear(screenSize);

		// 이중 버퍼 객체 생성 및 초기화
		screenBuffers[0] = new ScreenBuffer(screenSize);
		screenBuffers[0]->Clear();

		screenBuffers[1] = new ScreenBuffer(screenSize);
		screenBuffers[1]->Clear();

		// 활성화 버퍼 설정
		Present();
	}

	Renderer::~Renderer()
	{
		SafeDelete(frame);
		for (ScreenBuffer*& buffer : screenBuffers)
		{
			SafeDelete(buffer);
		}
	}

	void Renderer::Draw()
	{

	}

	Renderer& Renderer::Get()
	{
		if (!instance)
		{
			MessageBoxA(nullptr, "Renderer::Get() - instance is null", "Error", MB_OK);

			__debugbreak();
		}

		return *instance;
	}

	void Renderer::Clear()
	{

	}

	void Renderer::Submit(const char* text, const Vector2& position, Color color, int sortingOrder)
	{
	}

	void Renderer::Present()
	{
	}

	ScreenBuffer* Renderer::GetCurrentBuffer()
	{
		return nullptr;
	}

}