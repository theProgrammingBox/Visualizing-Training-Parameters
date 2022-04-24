
#include "header.h";

const Pixel Colors[16] = {
	Pixel(255, 0, 0, 255),
	Pixel(255, 127, 0, 255),
	Pixel(255, 255, 0, 255),
	Pixel(127, 255, 0, 255),
	Pixel(0, 255, 0, 255),
	Pixel(0, 255, 127, 255),
	Pixel(0, 255, 255, 255),
	Pixel(0, 127, 255, 255),
	Pixel(0, 0, 255, 255),
	Pixel(127, 0, 255, 255),
	Pixel(255, 0, 255, 255),
	Pixel(255, 0, 127, 255)
};

struct GraphData
{
	uint64_t RequiredConsecutiveOks;
	float GradientPrecision;
	float LearningRate;
	float PhantomCoefficient;
	float numTraining[NumTrainingPerRuns];
	float errorArr[NumRuns][NumTrainingPerRuns];
};

class Example : public olc::PixelGameEngine
{
private:
	GraphData* Graphs = new GraphData[NumItems];
	uint64_t RCOItem;
	uint64_t GPItem;
	uint64_t LRItem;
	uint64_t PCItem;
	uint64_t item;
	float zoom;
	float xOffset;
	float yOffset;

	void ReadFile()
	{
		ifstream file("Data.txt");
		string temp;

		if (file.peek() == ifstream::traits_type::eof())
		{
			cout << "Empty" << endl;
			throw "File Empty";
		}
		else
		{
			for (int item = 0; item < NumItems; item++)
			{
				GraphData data;
				file >> temp;
				file >> data.RequiredConsecutiveOks;
				if (temp != "RequiredConsecutiveOks:")
				{
					throw "Protocol error";
				}
				file >> temp;
				file >> data.GradientPrecision;
				if (temp != "GradientPrecision:")
				{
					throw "Protocol error";
				}
				file >> temp;
				file >> data.LearningRate;
				if (temp != "LearningRate:")
				{
					throw "Protocol error";
				}
				file >> temp;
				file >> data.PhantomCoefficient;
				if (temp != "PhantomCoefficient:")
				{
					throw "Protocol error";
				}
				for (int j = 0; j < NumRuns; j++)
				{
					file >> temp;
					file >> temp;
					for (int i = 0; i < NumTrainingPerRuns; i++)
					{
						file >> temp;
						file >> data.numTraining[i];
						file >> temp;
						file >> data.errorArr[j][i];
					}
				}
				Graphs[item] = data;
			}
		}
	}

public:
	Example()
	{
		sAppName = "Visualizing";
	}

	bool OnUserCreate() override
	{
		ReadFile();
		RCOItem = 0;
		GPItem = 0;
		LRItem = 0;
		PCItem = 0;
		item = 0;
		zoom = 10;
		xOffset = 0;
		yOffset = 0;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int run = 0; run < NumRuns; run++)
		{
			float* mx = new float((0 + xOffset) * zoom + ScreenWidth() / 2);
			float* my = new float(ScreenHeight() / 2 - (Graphs[item].errorArr[run][0] + yOffset) * zoom);
			for (int i = 1; i < NumTrainingPerRuns; i++)
			{
				float* mx2 = new float((i + xOffset) * zoom + ScreenWidth() / 2);
				float* my2 = new float(ScreenHeight() / 2 - (Graphs[item].errorArr[run][i] + yOffset) * zoom);
				DrawLine(
					*mx,
					*my,
					*mx2,
					*my2,
					BLACK);
				delete mx;
				delete my;
				mx = mx2;
				my = my2;
			}
			delete mx;
			delete my;
		}

		DrawString(0, 10, "RequiredConsecutiveOks: " + to_string(Graphs[item].RequiredConsecutiveOks) + " {<Y, H>}", BLACK, 2);
		DrawString(0, 40, "GradientPrecision: " + to_string(Graphs[item].GradientPrecision) + " {<U, J>}", BLACK, 2);
		DrawString(0, 70, "LearningRate: " + to_string(Graphs[item].LearningRate) + " {<I, K>}", BLACK, 2);
		DrawString(0, 100, "PhantomCoefficient: " + to_string(Graphs[item].PhantomCoefficient) + " {<O, L>}", BLACK, 2);

		if (GetKey(olc::Key::Y).bPressed) { RCOItem < 3 ? RCOItem++ : RCOItem = 0; }
		if (GetKey(olc::Key::H).bPressed) { RCOItem > 0 ? RCOItem-- : RCOItem = 3; }
		if (GetKey(olc::Key::U).bPressed) { GPItem < 3 ? GPItem++ : GPItem = 0; }
		if (GetKey(olc::Key::J).bPressed) { GPItem > 0 ? GPItem-- : GPItem = 3; }
		if (GetKey(olc::Key::I).bPressed) { LRItem < 3 ? LRItem++ : LRItem = 0; }
		if (GetKey(olc::Key::K).bPressed) { LRItem > 0 ? LRItem-- : LRItem = 3; }
		if (GetKey(olc::Key::O).bPressed) { PCItem < 3 ? PCItem++ : PCItem = 0; }
		if (GetKey(olc::Key::L).bPressed) { PCItem > 0 ? PCItem-- : PCItem = 3; }
		if (GetKey(olc::Key::UP).bHeld) { zoom += zoom * 0.01; }
		if (GetKey(olc::Key::DOWN).bHeld) { zoom > 0.01 ? zoom -= zoom * 0.01 : zoom = 0.01; }
		if (GetKey(olc::Key::A).bHeld) { xOffset += 3 / zoom; }
		if (GetKey(olc::Key::D).bHeld) { xOffset -= 3 / zoom; }
		if (GetKey(olc::Key::W).bHeld) { yOffset -= 3 / zoom; }
		if (GetKey(olc::Key::S).bHeld) { yOffset += 3 / zoom; }
		item = RCOItem + 4 * GPItem + 16 * LRItem + 64 * PCItem;

		for (int run = 0; run < NumRuns; run++)
		{
			float* mx = new float((0 + xOffset) * zoom + ScreenWidth() / 2);
			float* my = new float(ScreenHeight() / 2 - (Graphs[item].errorArr[run][0] + yOffset) * zoom);
			for (int i = 1; i < NumTrainingPerRuns; i++)
			{
				float* mx2 = new float((i + xOffset) * zoom + ScreenWidth() / 2);
				float* my2 = new float(ScreenHeight() / 2 - (Graphs[item].errorArr[run][i] + yOffset) * zoom);
				DrawLine(
					*mx,
					*my,
					*mx2,
					*my2,
					Colors[run & 15]);
				delete mx;
				delete my;
				mx = mx2;
				my = my2;
			}
			delete mx;
			delete my;
		}

		DrawString(0, 10, "RequiredConsecutiveOks: " + to_string(Graphs[item].RequiredConsecutiveOks), WHITE, 2);
		DrawString(0, 40, "GradientPrecision: " + to_string(Graphs[item].GradientPrecision), WHITE, 2);
		DrawString(0, 70, "LearningRate: " + to_string(Graphs[item].LearningRate), WHITE, 2);
		DrawString(0, 100, "PhantomCoefficient: " + to_string(Graphs[item].PhantomCoefficient), WHITE, 2);

		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(1000, 1000, 1, 1))
		demo.Start();

	return 0;
}