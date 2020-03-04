#pragma once

#include <JuceHeader.h>

class Plugin : public dB::Plugin
{
public:
    using ParameterLayout = juce::AudioProcessorValueTreeState::ParameterLayout;

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

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plugin)
};
