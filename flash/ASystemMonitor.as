class ASystemMonitor extends MovieClip
{
	var FrameRateHUDString:TextField;
	var loading:Boolean;
	var FrameTime:Number;
	var FrameDelta:Number;
	var FrameDeltaTime:Number;
	var FrameRate:Number;
	
	function ASystemMonitor()
	{
		super();
		loading = true;
		SetFrameRateHUDString("");
		FrameTime = 0;
		FrameDelta = 0;
		FrameDeltaTime = 0;
		FrameRate = 0;
	}
	
	public function SetFrameTime(aFrameTime:Number):Void
	{
		FrameTime = aFrameTime;
	}
	
	public function SetFrameDelta(aFrameDelta:Number):Void
	{
		FrameDelta = aFrameDelta;
	}
	
	public function SetFrameDeltaTime(aFrameDeltaTime:Number):Void
	{
		FrameDeltaTime = aFrameDeltaTime;
	}
	
	public function SetFrameRate(aFrameRate:Number):Void
	{
		FrameRate = aFrameRate;
	}
	
	public function CreateFrameString()
	{
		FrameRateHUDString.text = "FrameRate: " + String(FrameRate);
	}
	
	public function SetFrameRateHUDString(aFrameRateHUDString:String):Void
	{
		aFrameRateHUDString != undefined ? FrameRateHUDString.text = aFrameRateHUDString : FrameRateHUDString.text = "";
	}

}