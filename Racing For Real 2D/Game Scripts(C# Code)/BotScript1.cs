using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;

public struct BotTransform1
{
    public Vector3 position;
    public Quaternion rotation;
    public BotTransform1(Vector3 pos, Vector3 rot)
    {
        this.position = pos;
        this.rotation = Quaternion.Euler(rot);
    }
}
public class BotScript1 : MonoBehaviour
{
    private Transform car;
    public Transform botCar;
    private List<BotTransform1> recordedBotTransforms = new List<BotTransform1>();
    private BotTransform1 lastRecordedBotTransforms;
    private int iter;

    TextWriter tw;
    TextReader tr;
    private string PosX;
    private string PosY;
    private string RotZ;
    public static bool play;
    private float countdownTimer;

    void Start()
    {
        play = true;
        iter = 0;
        car = Garage.carSelected.transform;
        if(RaceLogic.trackSelected == "Race 1")
            tr = new StreamReader("Race1.1.txt");
        if(RaceLogic.trackSelected == "Race 2")
            tr = new StreamReader("Race2.1.txt");
        if(RaceLogic.trackSelected == "Race 3")
            tr = new StreamReader("Race3.1.txt");
        while(true)   
        {
            PosX = tr.ReadLine();
            PosY = tr.ReadLine();
            RotZ = tr.ReadLine();
            if(PosX == null || PosY == null || RotZ == null)
                break;
            Vector3 botCarPosition = new Vector3(float.Parse(PosX), float.Parse(PosY), 0);
            Vector3 botCarRotation = new Vector3(0, 0, float.Parse(RotZ));
            var newBotTransform = new BotTransform1(botCarPosition, botCarRotation);
            recordedBotTransforms.Add(newBotTransform);
        }
        countdownTimer = 4;
    }

    void Update()
    {
 
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
