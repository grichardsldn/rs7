class ToneGen;
class LFO;
class ADSR;
class Slewer;

class VolWidget;
class WidgetPanel;

class DeviceSub : public IDevice
{
	public:

	// IDevice stuff
	virtual void Init( 	IDeviceEvents *event,
				const char *instance_name, 
				int samplerate,
				const char *startup_params );
	virtual bool SetOutput( const char *output_name, int *output_ptr );
	virtual void Clock();
	virtual void MidiNoteOn( int channel, int note, int volume );
	virtual void MidiNoteOff( int channel, int note );
	virtual bool SetMidiInput( const char *input, int channel );

	DeviceSub();

	private:
	ToneGen *tonegen;
	ToneGen *sub_tonegen;
	ToneGen *noise_tonegen;
	ADSR *amp_adsr;
	LFO	*pwm_lfo;
	Slewer *slewer;
	int midi_channel;
	int note;
	int *output;
	int current_note;
	double pwm;
	double pitch_mod;
	double filt_level;
	double filt_env;
	double filt_lfo;
	double sub_vol;	
	double noise_vol;

	bool running;

	int octave_adjust;
	void CopyParams();
	VolWidget *amp_attack_widget;
	VolWidget *amp_decay_widget;
	VolWidget *amp_sustain_widget;
	VolWidget *amp_release_widget;
	VolWidget *pitch_mod_widget;
	VolWidget *pwm_widget;

	VolWidget *filt_level_widget;
	VolWidget *filt_env_widget;
	VolWidget *filt_lfo_widget;

	VolWidget *sub_vol_widget;
	VolWidget *noise_vol_widget;	
	
	WidgetPanel *panel;
};

