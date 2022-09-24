class rand_gen
{
private:
	unsigned int g_seed;
public:
	void Seed(unsigned int seed){g_seed=seed;}
	int Int(int min, int max)
	{
		g_seed=214013*g_seed+2531011;
		return min+(g_seed ^ g_seed>>15)%(max-min+1);
	}
	float Float(float min, float max)
	{
		g_seed=214013*g_seed+2531011;
		return min+(g_seed>>16)*(1.0f/65535.0f)*(max-min);
	}
	int Sign()
	{
		return Int(0,1)*2-1;
	}
};