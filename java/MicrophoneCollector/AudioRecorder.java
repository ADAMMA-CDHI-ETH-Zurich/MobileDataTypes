package MicrophoneCollector;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

import androidx.core.app.ActivityCompat;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;
import java.util.Collections;
import java.util.Vector;

import JavaCLAIDDataTypes.AudioData;

/**
 * Class managing the continuous recording and classification of audio from the microphone.
 * Audio is recorded in a separate thread and stored in a RingBuffer.
 * Depending on the classifciation mode, the recorded audio is classified continuously or
 * after the recording has stopped using a registered audio classifier with data from the RingBuffer.
 */
public class AudioRecorder
{
    // We only support MONO for now.
    private final int recorderChannels = AudioFormat.CHANNEL_IN_MONO;

    // We only support PCM_FLOAT for now.
    private final int recorderAudioEncoding = AudioFormat.ENCODING_PCM_FLOAT;


    private int sampleRate = 44100;


    private AudioRecord recorder = null;
    private Thread recordingThread = null;

    private boolean isRecording = false;



    private int getExpectedNumBytes(int secondsToRecord)
    {
        // TODO: Update when AudioFormat changes.
        // TODO: Update when number of channels changes.
        // TODO: Update when sample rate changes.
        return secondsToRecord * this.sampleRate * 4;
    }

    AudioRecorder(int sampleRate)
    {
        this.sampleRate = sampleRate;
    }

    @SuppressLint("MissingPermission")
    public boolean start()
    {
        recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
                this.sampleRate,
                this.recorderChannels,
                this.recorderAudioEncoding,
                AudioRecord.getMinBufferSize(this.sampleRate, this.recorderChannels,
                        this.recorderAudioEncoding));

        if(recorder.getState() != AudioRecord.STATE_INITIALIZED)
        {
            System.out.println("Failed to initialize recorder!");
            return false;
        }

        recorder.startRecording();
        return true;
    }


    @SuppressLint("MissingPermission")
    public AudioData record(int secondsToRecord) throws Exception {
        // Missing permission -> is checked externally in MainActivity.


        //  this.bufferSize = AudioRecord.getMinBufferSize(this.sampleRate, recorderChannels, this.recorderAudioEncoding);
        // 4 because float requires 4 byte.
        int bufferSizeInBytes;
        int floatBufferSize;

        floatBufferSize = this.sampleRate * secondsToRecord;
        bufferSizeInBytes = floatBufferSize * 4;

        int minBufferSize = secondsToRecord * sampleRate;//recorder.getMinBufferSize(sampleRate, recorderChannels, recorderAudioEncoding);
        float[] tmpBuffer = new float[minBufferSize];

        int readSize = recorder.read(tmpBuffer, 0, tmpBuffer.length, recorder.READ_BLOCKING);

        if(readSize * 4 != getExpectedNumBytes(secondsToRecord))
        {
            throw new IOException("Error in AudioRecorder: Requested to record " + secondsToRecord +
                    " of data, which would be " + getExpectedNumBytes(secondsToRecord) + " of bytes given "+
                    " the current configuration of the recorder, however only " + readSize*4 + " bytes were recorded.");
        }

        // convert float to byte
        byte[] bytes = new byte[bufferSizeInBytes];
        ByteBuffer.wrap(bytes).order(ByteOrder.nativeOrder()).asFloatBuffer().put(tmpBuffer);
        AudioData audioData = new AudioData();

        audioData.set_data(bytes);

        return audioData;
    }

    /**
     * Stops the recording and releases the audio recorder.
     */
    public void stopRecording()
    {
        if (this.isRecording)
        {
            this.isRecording = false;

            if (this.recorder.getState() == AudioRecord.RECORDSTATE_RECORDING)
            {
                this.recorder.stop();
            }
            // Release recorder. Otherwise, on some android devices,
            // recording can not be restarted (at least if this.audioRecord is always
            // reinitialized), as the microphone is always locked.
            this.recorder.release();
        }
    }


}