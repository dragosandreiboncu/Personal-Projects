using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;

public struct BotTransform
{
    public Vector3 position;
    public Quaternion rotation;
    public BotTransform(Vector3 pos, Vector3 rot)
    {
        this.position = pos;
        this.rotation = Quaternion.Euler(rot);
         //this.position = pos;
         //this.rotation = rot;
    }
}
public class BotScript : MonoBehaviour
{
    private Transform car;
    public Transform botCar;
    private List<BotTransform> recordedBotTransforms = new List<BotTransform>();
    private BotTransform lastRecordedBotTransforms;
    private int iter;

    TextWriter tw;
    TextReader tr;
    private string PosX;
    private string PosY;
    private string RotZ;
    public static bool play;
    public float countdownTimer;

    void Start()
    {
        play = true;
        iter = 0;
        car = Garage.carSelected.transform;
        if(RaceLogic.trackSelected == "Race 1")
            tr = new StreamReader("Race1.txt");
            //tw = new StreamWriter("Race1.4.txt");
        if(RaceLogic.trackSelected == "Race 2")
            tr = new StreamReader("Race2.txt");
            //tw = new StreamWriter("Race2.4.txt");
        if(RaceLogic.trackSelected == "Race 3")
            tr = new StreamReader("Race3.txt");
            //tw = new StreamWriter("Race3.4.txt");
        if(RaceLogic.trackSelected == "Race 4")
            tr = new StreamReader("Race4.txt");
            //tw = new StreamWriter("Race4.4.txt");
        if(RaceLogic.trackSelected == "Race 5")
            tr = new StreamReader("Race5.txt");
            //tw = new StreamWriter("Race5.txt");   
        while(true)   
        {
            PosX = tr.ReadLine();
            PosY = tr.ReadLine();
            RotZ = tr.ReadLine();
            if(PosX == null || PosY == null || RotZ == null)
                break;
            Vector3 botCarPosition = new Vector3(float.Parse(PosX), float.Parse(PosY), 0);
            Vector3 botCarRotation = new Vector3(0, 0, float.Parse(RotZ));
            var newBotTransform = new BotTransform(botCarPosition, botCarRotation);
            recordedBotTransforms.Add(newBotTransform);
        }
        countdownTimer = 4;
    }

    void Update()
    {
        /*if(car.position != lastRecordedBotTransforms.position || car.rotation != lastRecordedBotTransforms.rotation)
        {
             var newBotTransform = new BotTransform(car.position, car.rotation);
             tw.WriteLine(newBotTransform.position.x);
             tw.WriteLine(newBotTransform.position.y);
             tw.WriteLine(newBotTransform.rotation.eulerAngles.z);
             lastRecordedBotTransforms = newBotTransform;
        }*/
 
        if(countdownTimer > 0)
        {
            countdownTimer -= Time.deltaTime;
            botCar.position = recordedBotTransforms[0].position;
            botCar.rotation = recordedBotTransforms[0].rotation;
        }
        else
            if(play)
                Play();
    }

    void Play()
    {
        StartCoroutine(StartBot());
        play = false;
    }

    IEnumerator StartBot()
    {
        for(int i = iter; i < recordedBotTransforms.Count; i++)
        {
            iter++;
            botCar.position = recordedBotTransforms[i].position;
            botCar.rotation = recordedBotTransforms[i].rotation;
            yield return new WaitForFixedUpdate();
        }
    }
}
