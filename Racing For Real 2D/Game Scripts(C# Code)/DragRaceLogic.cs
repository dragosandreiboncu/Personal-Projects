using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class DragRaceLogic : MonoBehaviour
{

    public float laps;
    public GameObject menu;
    public GameObject speed;
    public TextMeshProUGUI RaceTimer;
    public static float lapsCounter;
    private bool BeatLevel;
    public float BeatLevelTime;
    public static string trackSelected = null;
    TextMeshProUGUI CounterText;
    private GameObject car;
    private GameObject botCar;
    public GameObject light1;
    public GameObject light2;
    public GameObject light3;
    public GameObject light4;
    public static bool start;
    public static bool finish;
    private float countdownTimer;
    private float countdownTimerInit;
    private float raceTimer;
    private TimeSpan racePlaying;
    public Slider rpm;
    public Slider nitro;
    // Start is called before the first frame update
    void Start()
    {
        string carName = Garage.carSelected.name;
        car = GameObject.Find("Race 5 Root").transform.Find(carName).gameObject;
        car.SetActive(true);
        int botNr = UnityEngine.Random.Range(1, 8);
        string botCarName = "BotCar" + botNr;
        botCar = GameObject.Find("RaceLogic").transform.Find(botCarName).gameObject;
        botCar.SetActive(true);
        //car.transform.position = new Vector3(-1621, -3595, 0);
        car.transform.position = new Vector3(-1580, -3605, 0);
        car.transform.eulerAngles = new Vector3(0, 0, 0);

        CounterText = GetComponent<TextMeshProUGUI>();
        start = true;
        finish = false;

        countdownTimer = UnityEngine.Random.Range(5, 9);
        countdownTimerInit = countdownTimer;
        lapsCounter = 1;
        raceTimer = 0;
        BeatLevel = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(!finish)
        {
            rpm.value = DragCarScript.rpm;
            nitro.value = DragCarScript.nitro;
            string gear = "";
            if(DragCarScript.currentGear == 0)
                gear += "N";
            if(DragCarScript.currentGear == 1)
                gear += "1st";
            if(DragCarScript.currentGear == 2)
                gear += "2nd";
            if(DragCarScript.currentGear == 3)
                gear += "3rd";
            if(DragCarScript.currentGear > 3)
                gear += DragCarScript.currentGear + "th";
            speed.GetComponent<TextMeshProUGUI>().text = "Speed:" + (int)(DragCarScript.carSpeed * 1.1) + " km/h \n" + "Gear:" + gear;
        }
        if(start)
        {
            if (countdownTimer > 0)
            {
                botCar.GetComponent<BotScript>().countdownTimer = 1;
                if(countdownTimer >= countdownTimerInit - 1)
                    light1.SetActive(true);
                else if(countdownTimer >= countdownTimerInit - 2)
                    light2.SetActive(true);
                else if(countdownTimer >= countdownTimerInit - 3)
                    light3.SetActive(true);
                else if(countdownTimer <= 1)
                {
                    botCar.GetComponent<BotScript>().countdownTimer = -1;
                    CounterText.text = "GO";
                    light4.SetActive(true);
                }
                countdownTimer -= Time.deltaTime;
                if(DragCarScript.carSpeed == 0)
                    DragCarScript.rpm = (countdownTimerInit - countdownTimer) * 10;
                else if(DragCarScript.carSpeed > 0 && DragCarScript.currentGear != 0 && countdownTimer > 1)
                {
                    start = false;
                    finish = true;
                    BeatLevel = false;
                    CounterText.text = "YOU LOST";
                    speed.GetComponent<TextMeshProUGUI>().text = "";
                    nitro.gameObject.SetActive(false);
                    rpm.gameObject.SetActive(false);
                    countdownTimer = 2;
                    light1.SetActive(false);
                    light2.SetActive(false);
                    light3.SetActive(false);
                    light4.SetActive(false);
                }
            }
            else
            {
                light1.SetActive(false);
                light2.SetActive(false);
                light3.SetActive(false);
                light4.SetActive(false);
                CounterText.text = "";
                start = false;
            }
        }
        else if(finish)
        {
            if (countdownTimer > 0)
                countdownTimer -= Time.deltaTime;
            else
            {
                if(BeatLevel)
                    menu.GetComponent<PauseManager>().Finish();
                else
                    menu.GetComponent<PauseManager>().Abandon();
            }
        }
        else
        {
            if(lapsCounter > laps)
            {
                finish = true;
                countdownTimer = 2;
                raceTimer += Time.deltaTime;
                if(raceTimer <= BeatLevelTime)
                {
                    CounterText.text = "YOU WON";
                    BeatLevel = true;
                }
                else
                {
                    CounterText.text = "YOU LOST";
                    BeatLevel = false;
                }
                speed.GetComponent<TextMeshProUGUI>().text = "";
                nitro.gameObject.SetActive(false);
                rpm.gameObject.SetActive(false);
            }
            else
            {
                raceTimer += Time.deltaTime;
                racePlaying = TimeSpan.FromSeconds(raceTimer);
                string raceTimerStr = "Time:" + racePlaying.ToString("mm':'ss'.'ff");
                RaceTimer.text = raceTimerStr;
            }
        }
    }
}
