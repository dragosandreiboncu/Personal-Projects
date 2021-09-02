using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class MenuManager : MonoBehaviour
{
    public GameObject ContinueGameButton;
    private GameObject saved;

    void Update()
    {
        saved = GameObject.Find("GarageRoot1");
        if(saved != null) 
            ContinueGameButton.SetActive(true);
        else
            ContinueGameButton.SetActive(false);
    }
    public void StartGame()
    {
        PlayerPrefs.SetInt("starting money", 50000);
        SceneManager.LoadScene("Garage");
    }
    public void ContinueGame()
    {   
        saved = GameObject.Find("GarageRoot1");
        saved.transform.Find("GarageRoot2").gameObject.SetActive(true);
        SceneManager.UnloadSceneAsync("Menu");
    }
    public void QuitGame()
    {
        Application.Quit();
    }
}
