using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseManager : MonoBehaviour
{
    public static bool isPaused = false;
    public GameObject pauseMenu;
    public GameObject LoadingScreen;
    public GameObject raceLogic;
    private GameObject saved;
    private GameObject music;
    public static int money;
    public int trackPrize;
    public static bool raceWon = false;
    public static bool raceLost = false;
    private float timeRemaining = 2f;
    private bool buttonPressed = false;
    void Start()
    {
        music = GameObject.Find("MainMenuRoot1").transform.Find("Music").gameObject;
        music.SetActive(false);
        money = PlayerPrefs.GetInt("money after track select");
    }
    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Escape) && !buttonPressed)
        {
            if(isPaused)
                Resume();
            else
                Pause();
        }
        if(buttonPressed)
        {
            if (timeRemaining > 0)
                timeRemaining -= Time.deltaTime;
            else
            {
                saved = GameObject.Find("GarageRoot1");
                if(saved != null) 
                {
                    music.SetActive(true);
                    saved.transform.Find("GarageRoot2").gameObject.SetActive(true);
                    Garage.carSelected.SetActive(false);
                    SceneManager.UnloadSceneAsync(Races.trackSelected);
                }
            }
        }
    }
    public void QuitGame()
    {
        Application.Quit();
    }
    public void Abandon()
    {
        raceLost = true;
        buttonPressed = true;
        pauseMenu.SetActive(false);
        LoadingScreen.SetActive(true);
        raceLogic.SetActive(false);
        PlayerPrefs.SetInt("money after race lost", money);
        timeRemaining = 2f;
        Time.timeScale = 1f;
    }
    public void Resume()
    {
        pauseMenu.SetActive(false);
        raceLogic.SetActive(true);
        BotScript.play = true;
        Time.timeScale = 1f;
        isPaused = false;
    }
    public void Pause()
    {
        pauseMenu.SetActive(true);
        raceLogic.SetActive(false);
        Time.timeScale = 0f;
        isPaused = true;
    }
    public void Finish()
    {
        money += trackPrize;
        raceWon = true;
        buttonPressed = true;
        pauseMenu.SetActive(false);
        LoadingScreen.SetActive(true);
        raceLogic.SetActive(false);
        PlayerPrefs.SetInt("money after race win", money);
        timeRemaining = 2f;
    }
}
