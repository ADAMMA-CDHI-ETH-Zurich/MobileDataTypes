package MicrophoneCollector;
import android.os.Handler;

import androidx.appcompat.app.AppCompatActivity;
import AndroidPermissions.MicrophonePermission;
import JavaCLAID.Channel;
import JavaCLAID.ChannelData;
import JavaCLAID.Module;
import JavaCLAIDDataTypes.AudioData;
import JavaCLAIDDataTypes.Request;

public class MicrophoneCollector extends Module
{
    private Channel audioDataChannel;
    private Channel requestChannel;
    private AppCompatActivity activity;
    private AudioRecorder recorder;
    private final String DATA_IDENTIFIER = "MicrophoneAudioData";

  /*  public void reflect(Reflector reflector)
    {
        reflector.reflectMember("test");
    }*/

    public void initialize()
    {
        System.out.println("Calling init of MicrophoneCollector");
        new MicrophonePermission().blockingRequest();
        this.recorder = new AudioRecorder(16000);
        this.recorder.start();
        this.requestChannel = this.subscribe(Request.class, "Requests", "onRequest");
        this.audioDataChannel = this.publish(AudioData.class, DATA_IDENTIFIER);
        System.out.println("Microphone collector initialized");
    }

    public void onRequest(ChannelData<Request> data)
    {
        Request r = data.value();

        if(r.get_dataIdentifier().compareTo(DATA_IDENTIFIER) == 0)
        {
            onAudioDataRequested(r);
        }
    }

    public void onAudioDataRequested(Request r)
    {
        //Integer length = r.get_length();
        Integer length = 2;
        System.out.println("Received request to record audio data for " + length + " seconds.");

        AudioData data = null;
        try {
            data = recorder.record(length);
        } catch (Exception e) {
            e.printStackTrace();
        }

        if(data != null)
        {
            System.out.println("Recorded data");
            audioDataChannel.post(data);
        }
        else
        {
            System.out.println("Data invalid");
        }
    }
}
