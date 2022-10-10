using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System.Text;
public class MenuManager : MonoBehaviour
{
    public GameObject ContinueGameButton;
    private string saved;
    private string data;
    public List<int> continueData;
    TextReader tr;
    TextWriter tw;
    GameObject cars;

    void Start()
    {
        CheckSave();
    }
    public void CheckSave()
    {
        tr = new StreamReader("Save.txt");
        saved = tr.ReadLine();
        if(saved == "1")
        {
            continueData = new List<int>();
            ContinueGameButton.SetActive(true);
            while(true)   
            {
                data = tr.ReadLine();
                if(data == null)
                    break;
                continueData.Add(int.Parse(data));
            }
        }
        else
        {
            ContinueGameButton.SetActive(false);
            continueData = null;
        }
        tr.Close();
    }
    public void StartGame()
    {
        tw = new StreamWriter("Save.txt");
        tw.WriteLine("0");
        tw.Close();
        PlayerPrefs.SetInt("starting money", 5000);
        SceneManager.LoadScene("Garage", LoadSceneMode.Additive);
        GameObject.Find("MainMenuRoot2").SetActive(false);
    }
    public void ContinueGame()
    {   
        PlayerPrefs.SetInt("starting money", continueData[0]);
        SceneManager.LoadScene("Garage", LoadSceneMode.Additive);
        GameObject.Find("MainMenuRoot2").SetActive(false);
    }
    public void QuitGame()
    {
        Application.Quit();
    }
}
