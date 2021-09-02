using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class RaceLogic : MonoBehaviour
{
    public float laps;
    public GameObject menu;
    public GameObject lapsShow;
    public GameObject wrongDirectionText;
    public GameObject speed;
    public TextMeshProUGUI RaceTimer;
    public static float lapsCounter;
    private bool BeatLevel;
    public float BeatLevelTime;
    public static string trackSelected = null;
    TextMeshProUGUI CounterText;
    private GameObject car;
    private bool start;
    private bool finish;
    public static bool wrongDirection;
    public static bool checkpointTaken;
    private float countdownTimer;
    private float raceTimer;
    private TimeSpan racePlaying;
    // Start is called before the first frame update
    void Start()
    {
        car = Garage.carSelected;
        car.SetActive(true);
        if(trackSelected == "Race 1")
        {
            car.transform.position = new Vector3(790, 141, 0);
            car.transform.eulerAngles = new Vector3(0, 0, 0);
        }
        if(trackSelected == "Race 2")
        {
            car.transform.position = new Vector3(315, 115, 0);
            car.transform.eulerAngles = new Vector3(0, 0, 30);
        }
        if(trackSelected == "Race 3")
        {
            car.transform.position = new Vector3(445, 95, 0);
            car.transform.eulerAngles = new Vector3(0, 0, -90);
        }
        if(trackSelected == "Race 4")
        {
            car.transform.position = new Vector3(400, 90, 0);
            car.transform.eulerAngles = new Vector3(0, 0, 90);
        }
        CounterText = GetComponent<TextMeshProUGUI>();
        start = true;
        finish = false;
        countdownTimer = 4;
        GameObject.FindWithTag("Player").GetComponent<CarScript>().enabled = false;
        lapsCounter = 1;
        checkpointTaken = false;
        wrongDirection = false;
        raceTimer = 0;
        BeatLevel = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(start)
        {
            lapsShow.GetComponent<TextMeshProUGUI>().text = "";
            if (countdownTimer > 0)
            {
                if(countdownTimer >= 3)
                    CounterText.text = "" + 3;
                else if(countdownTimer >= 2)
                    CounterText.text = "" + 2;
                else if(countdownTimer >= 1)
                    CounterText.text = "" + 1;
                else if(countdownTimer >= 0)
                    CounterText.text = "GO";
                countdownTimer -= Time.deltaTime;
            }
            else
            {
                CounterText.text = "";
                start = false;
                GameObject.FindWithTag("Player").GetComponent<CarScript>().enabled = true;
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
                GameObject.FindWithTag("Player").GetComponent<CarScript>().enabled = false;
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
            }
            else
            {
                lapsShow.GetComponent<TextMeshProUGUI>().text = lapsCounter + "/" + laps;
                speed.GetComponent<TextMeshProUGUI>().text = "Speed " + (int)(CarScript.carSpeed * 1.1) + " km/h";
                raceTimer += Time.deltaTime;
                racePlaying = TimeSpan.FromSeconds(raceTimer);
                string raceTimerStr = "" + racePlaying.ToString("mm':'ss'.'ff");
                RaceTimer.text = raceTimerStr;
            }
            if(wrongDirection)
                wrongDirectionText.SetActive(true);
            else
                wrongDirectionText.SetActive(false);
        }
    }
}
