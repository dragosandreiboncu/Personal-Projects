using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;

public struct BotTransform2
{
    public Vector3 position;
    public Quaternion rotation;
    public BotTransform2(Vector3 pos, Vector3 rot)
    {
        this.position = pos;
        this.rotation = Quaternion.Euler(rot);
    }
}
public class BotScript2 : MonoBehaviour
{
    private Transform car;
    public Transform botCar;
    private List<BotTransform2> recordedBotTransforms = new List<BotTransform2>();
    private BotTransform2 lastRecordedBotTransforms;
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
            tr = new StreamReader("Race1.2.txt");
        if(RaceLogic.trackSelected == "Race 3")
            tr = new StreamReader("Race3.2.txt");
        while(true)   
        {
            PosX = tr.ReadLine();
            PosY = tr.ReadLine();
            RotZ = tr.ReadLine();
            if(PosX == null || PosY == null || RotZ == null)
                break;
            Vector3 botCarPosition = new Vector3(float.Parse(PosX), float.Parse(PosY), 0);
            Vector3 botCarRotation = new Vector3(0, 0, float.Parse(RotZ));
            var newBotTransform = new BotTransform2(botCarPosition, botCarRotation);
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
