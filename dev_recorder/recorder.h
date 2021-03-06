// This is a test device
// requires stdio.h

class Channel
{
	public:
	char filename[1024];
	FILE *ptr;
	bool output;
	int *connection;

	Channel();
	Channel *next;
};


class DeviceRecorder : public IDevice
{
	public:

	// IDevice stuff
	virtual void Init( 	IDeviceEvents *event,
				const char *instance_name, 
				int samplerate,
				const char *startup_params );
	virtual bool SetInput( const char *input_name, int *input_ptr );
	virtual bool SetOutput( const char *output_name, int *outptr_ptr );
	virtual void Clock();
	virtual bool TransportPlay();
	virtual bool TransportStop();

	DeviceRecorder();

	private:
	//char filename[1024];
	bool playing;
	//int *input;
	//FILE *outfile;

	Channel *head;
};

