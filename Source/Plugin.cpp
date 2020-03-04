#include "Plugin.hpp"
#include "PluginEditor.hpp"


Plugin::Plugin() : dB::Plugin(createDefaultIO(), createParameters())
{

}


juce::StringArray
Plugin::getAlternateDisplayNames() const
{
    return {JucePlugin_Name};
}


juce::AudioProcessor::BusesProperties
Plugin::createDefaultIO()
{
    return BusesProperties()
        .withInput ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true);
}


juce::AudioProcessorValueTreeState::ParameterLayout
Plugin::createParameters()
{
    return {};
}


void
Plugin::prepareToPlay(
    const double /* sampleRate      */,
    const int    /* samplesPerBlock */)
{

}


bool
Plugin::isBusesLayoutSupported(
    const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
    &&  layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}


void
Plugin::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& /* midiMessages */)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}


void
Plugin::processBlockBypassed(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages)
{
    processBlock(buffer, midiMessages);
}


bool
Plugin::hasEditor() const
{
    return true;
}


juce::AudioProcessorEditor*
Plugin::createEditor()
{
    return new PluginEditor(*this);
}


juce::AudioProcessor*
JUCE_CALLTYPE createPluginFilter()
{
    return new Plugin();
}
