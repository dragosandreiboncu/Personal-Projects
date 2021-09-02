using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Races : MonoBehaviour
{
    public GameObject LoadingScreen;
    public GameObject Track1;
    public GameObject Track2;
    public GameObject Track3;
    public GameObject Track4;

    public static string trackSelected = null;
    private float timeRemaining = 2;
    private GameObject saved;

    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Escape))
            Back();
        if(Track1.activeSelf)
            trackSelected = "Race 1";
        if(Track2.activeSelf)
            trackSelected = "Race 2";
        if(Track3.activeSelf)
            trackSelected = "Race 3";
        if(Track4.activeSelf)
            trackSelected = "Race 4";
        if(LoadingScreen.activeSelf)
        {
            if (timeRemaining > 0)
                timeRemaining -= Time.deltaTime;
            else
            {
                SceneManager.LoadScene(trackSelected, LoadSceneMode.Additive);
                RaceLogic.trackSelected = trackSelected;
                SceneManager.UnloadSceneAsync("Races");
            }
        }
                
    }
    public void Back()
    {
        saved = GameObject.Find("GarageRoot1");
        if(saved != null) 
        {
            saved.transform.Find("GarageRoot2").gameObject.SetActive(true);
            SceneManager.UnloadSceneAsync("Races");
        }
    }
}
