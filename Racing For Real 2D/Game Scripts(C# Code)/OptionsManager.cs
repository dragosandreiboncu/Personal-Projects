using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.UI;
using TMPro;
public class OptionsManager : MonoBehaviour
{
    public TextMeshProUGUI VolumeLive; 
    public AudioMixer audioMixer;
    public void SetVolume(float volume)
    {
        audioMixer.SetFloat("volume", volume);
        VolumeLive.text = "" + (((int)volume + 50) * 2);
    }
    public void SetQuality(int qualityIndex)
    {
        QualitySettings.SetQualityLevel(2-qualityIndex);
    }
    public void SetFullScreen(bool isFullScreen)
    {
        Screen.fullScreen = isFullScreen;
    }
}
