package BatteryCollector;

import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import JavaCLAID.CLAID;
import JavaCLAID.Channel;
import JavaCLAID.ChannelData;
import JavaCLAID.Module;
import JavaCLAID.Reflector;
import JavaCLAIDDataTypes.BatteryData;
import JavaCLAIDDataTypes.Request;

public class BatteryCollector extends Module
{
    private Channel<BatteryData> batteryDataChannel;
    private Channel<Request> batteryRequestsChannel;

    private final String DATA_IDENTIFIER = "BatteryData";
    String outputChannel = DATA_IDENTIFIER;

    public void initialize()
    {
        System.out.println("Calling init of BatteryCollector");
        this.batteryDataChannel = this.publish(BatteryData.class, this.outputChannel);
        this.batteryRequestsChannel = this.subscribe(Request.class, "Requests", r -> onBatteryDataRequested(r));
        System.out.println("BatteryCollector initialized");
    }

    public void reflect(Reflector r)
    {
        r.reflectWithDefaultValue("outputChannel", this.outputChannel, DATA_IDENTIFIER);

    }

    public void onBatteryDataRequested(ChannelData<Request> data)
    {
        System.out.println("On request in battery");
        Request request = data.value();

        if(request.get_dataIdentifier().equals(DATA_IDENTIFIER))
        {
            System.out.println("BatteryData requested");
            this.postBatteryData();
        }
    }


    public void postBatteryData()
    {
        IntentFilter intentFilter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
        Context context = (Context) CLAID.getContext();
        Intent batteryStatus = context.registerReceiver(null, intentFilter);

        BatteryData batteryData = BatteryIntentHelper.extractBatteryDataFromIntent(batteryStatus);

        batteryDataChannel.post(batteryData);
    }




}
