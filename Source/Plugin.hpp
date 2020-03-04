#pragma once

#include <JuceHeader.h>

class Plugin : public dB::Plugin
{
    using ParameterLayout = juce::AudioProcessorValueTreeState::ParameterLayout;

public:
    struct ParamIds
    {
        static const juce::StringRef Input;
        static const juce::StringRef Output;
        static const juce::StringRef Brightness;
        static const juce::StringRef Drive;
        static const juce::StringRef Overdrive;
        static const juce::StringRef InputMeter;
        static const juce::StringRef OutputMeter;
    };

    Plugin();
    ~Plugin() = default;

    juce::StringArray getAlternateDisplayNames() const override;

    static BusesProperties createDefaultIO();
    static ParameterLayout createParameters();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlockBypassed(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    struct
    {
        std::atomic<float>* input;
        std::atomic<float>* output;
        std::atomic<float>* brightness;
        std::atomic<float>* drive;
        std::atomic<float>* overdrive;

        juce::RangedAudioParameter* inputMeter;
        juce::RangedAudioParameter* outputMeter;
    } params;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plugin)
};
