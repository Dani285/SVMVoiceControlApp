// The contents of this file are in the public domain. See
// LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This is an example illustrating the use of the support vector machine
    utilities from the dlib C++ Library.

    This example creates a simple set of data to train on and then shows
    you how to use the cross validation and svm training functions
    to find a good decision function that can classify examples in our
    data set.


    The data used in this example will be 2 dimensional data and will
    come from a distribution where points with a distance less than 10
    from the origin are labeled +1 and all other points are labeled
    as -1.

*/
#include <dlib/svm.h>
#include <iostream>
#define MINIMP3_IMPLEMENTATION
#include <minimp3/minimp3.h>
#include <QString>
#include <QFile>
#include <QtCore>
#include <vector>
#include "aquila/aquila.h"
#include <QtConcurrent/QtConcurrent>

dlib::matrix<double> ExtractFeatures(int32_t size, const std::vector<Aquila::SampleType> & samples, size_t CAPFeatures) {
    Q_ASSERT(size>0);
    Q_ASSERT(size<=14);
    int32_t chunk = 1 << size;
    std::vector<double> values;
    int32_t current = 0;
    while (current <= samples.size()) {
        // int32_t end = std::min<int32_t>(samples.size(), current + chunk);
        if (samples.size()<current+chunk) break;

        std::vector<Aquila::SampleType> Sample(samples.begin()+current, samples.begin()+current+chunk);
        current+=chunk;
        Aquila::SignalSource signalSource(Sample, 48000.0);
        // std::cout << "signalSource.getSamplesCount() = " << signalSource.getSamplesCount() << std::endl;
        // std::cout << "time: " << static_cast<double>(Sample.size()) / 48000.0 << "s" <<  std::endl;
        Aquila::Mfcc mfcc(Sample.size());
        auto mfccValues = mfcc.calculate(signalSource);
        values.insert(values.end(),mfccValues.begin(), mfccValues.end());

        // std::cout << "MFCC coefficients: \n";
        // std::copy(
        //     std::begin(mfccValues),
        //     std::end(mfccValues),
        //     std::ostream_iterator<double>(std::cout, " ")
        //     );
    }
    auto cap = std::min(values.size(), CAPFeatures);
    dlib::matrix<double, 0, 1> result(cap);
    for (int32_t q=0; q< cap; q++) {
        result(q)= values.at(q);
    }
    return result;

}


std::vector<Aquila::SampleType> ReadMP3File( QString FileName) {
    QFile file(FileName);
    file.open(QIODeviceBase::ReadOnly);

    QVector<char> buffer(10000000);
    int64_t bufferSize=-1;
    bufferSize = file.read(buffer.data(), buffer.size());
    // qDebug() << "bufferSize = " << bufferSize;
    mp3dec_t mp3d;
    mp3dec_init(&mp3d);

    /*typedef struct
    {
        int frame_bytes;
        int channels;
        int hz;
        int layer;
        int bitrate_kbps;
    } mp3dec_frame_info_t;*/
    mp3dec_frame_info_t info;
    short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
    std::vector<Aquila::SampleType> PCM;
    /*unsigned char *input_buf; - input byte stream*/

    int64_t start = 0;

    while (true) {

        int frames = mp3dec_decode_frame(&mp3d, reinterpret_cast<uint8_t*>(buffer.data()+start), bufferSize, pcm, &info);

        if (frames<=0) break;
        start+=info.frame_bytes;
        // qDebug() << "info.frame_bytes = " << info.frame_bytes;
        // qDebug() << "info.channels = " << info.channels;
        // qDebug() << "info.hz = " << info.hz;
        // qDebug() << "info.layer = " << info.layer;
        // qDebug() << "info.bitrate_kbps = " << info.bitrate_kbps;
        for (int64_t w=0; w<frames; w++)
            PCM.push_back(pcm[w]);
    }

    return PCM;
}

void SaveRAWFile(QString FileName, const std::vector<Aquila::SampleType> & PCM ) {
    /*
    QFile outfile("_file.raw");
    outfile.open(QIODevice::WriteOnly);
    QDataStream out(&outfile);
    out.writeRawData(reinterpret_cast<char*>(PCM.data()), sizeof(short)*PCM.size());
    */
}

using sample_type = dlib::matrix<double>;
using kernel_type = dlib::radial_basis_kernel<sample_type>;


int main()
{


    QThreadPool::globalInstance();
    qDebug() << "QThreadPool::globalInstance()->activeThreadCount() = " << QThreadPool::globalInstance()->activeThreadCount();
    QString array[50];
    QString filename("/Users/dani2000/Downloads/single/cv-corpus-7.0-singleword/en/clips/");
    QString trainingData("/Users/dani2000/Downloads/single/cv-corpus-7.0-singleword/en/train.tsv");

    QFile trainingFile(trainingData);
    trainingFile.open(QIODeviceBase::ReadOnly);

    QString selectedFile;

    /*
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFreq = 48000, f1 = 125, f2 = 700;

    Aquila::SineGenerator sine1(sampleFreq);
    sine1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Aquila::SineGenerator sine2(sampleFreq);
    sine2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
    auto sum = sine1 + sine2;

    Aquila::TextPlot plot("Input");
    plot.plot(sum);

    auto fft = Aquila::FftFactory::getFft(SIZE);
    Aquila::SpectrumType spectrum = fft->fft(sum.toArray());

    plot.setTitle("Spectrum");
    plot.plotSpectrum(spectrum);
    */

    // {
    //     const std::size_t SIZE = 1024;
    //     const Aquila::FrequencyType sampleFrequency = 1024;

    //     Aquila::SineGenerator input(sampleFrequency);
    //     input.setAmplitude(5).setFrequency(64).generate(SIZE);

    //     Aquila::Mfcc mfcc(input.getSamplesCount());
    //     auto mfccValues = mfcc.calculate(input);
    //     std::cout << "MFCC coefficients: \n";
    //     std::copy(
    //         std::begin(mfccValues),
    //         std::end(mfccValues),
    //         std::ostream_iterator<double>(std::cout, " ")
    //         );
    //     std::cout << "\n";
    // }



    trainingFile.readLine();
    int32_t min = std::numeric_limits<int32_t>::max();
    std::vector<sample_type> samples;
    std::vector<double> labels;

    while (!trainingFile.atEnd()) {
        auto line = trainingFile.readLine();
        auto values = line.split('\t');
        auto audioFileName = values.at(1);
        auto word = values.at(2);
        // qDebug() << values.at(2);
        // qDebug() << "word = " << word;

        auto PCM = ReadMP3File(filename+audioFileName);
        // qDebug() << "filename+audioFileName = " << filename+audioFileName;
        auto features = ExtractFeatures(12, PCM, 200);
        // qDebug() << "features.size() = " << features.size();
        if (features.size()<200) continue;
        samples.push_back(features);
        if (word=="three") {
            labels.push_back(1.0);
        } else {
            labels.push_back(-1.0);
        }
    }
    qDebug() << "samples.size() = " << samples.size();
    qDebug() << "labels.size() = " << labels.size();

    /*
    QDirIterator it("/Users/dani2000/Downloads/cv-corpus-19.0-delta-2024-09-13/en/clips/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.filePath();
        it.next();
    }
    */





  // Here we normalize all the samples by subtracting their mean and dividing by
  // their standard deviation.  This is generally a good idea since it often
  // heads off numerical stability problems and also prevents one large feature
  // from smothering others.  Doing this doesn't matter much in this example so
  // I'm just doing this here so you can see an easy way to accomplish this with
  // the library.
  dlib::vector_normalizer<sample_type> normalizer;
  // let the normalizer learn the mean and standard deviation of the samples
  normalizer.train(samples);
  // now normalize each sample
  for (unsigned long i = 0; i < samples.size(); ++i)
    samples[i] = normalizer(samples[i]);

  // Now that we have some data we want to train on it.  However, there are two
  // parameters to the training.  These are the nu and gamma parameters.  Our
  // choice for these parameters will influence how good the resulting decision
  // function is.  To test how good a particular choice of these parameters is
  // we can use the cross_validate_trainer() function to perform n-fold cross
  // validation on our training data.  However, there is a problem with the way
  // we have sampled our distribution above.  The problem is that there is a
  // definite ordering to the samples.  That is, the first half of the samples
  // look like they are from a different distribution thans the second half. This
  // would screw up the cross validation process but we can fix it by
  // randomizing the order of the samples with the following function call.
  randomize_samples(samples, labels);

  // The nu parameter has a maximum value that is dependent on the ratio of the
  // +1 to -1 labels in the training data.  This function finds that value.
  const double max_nu = dlib::maximum_nu(labels);

  // here we make an instance of the svm_nu_trainer object that uses our kernel
  // type.

  // Now we loop over some different nu and gamma values to see how good they
  // are.  Note that this is a very simple way to try out a few possible
  // parameter choices.  You should look at the model_selection_ex.cpp program
  // for examples of more sophisticated strategies for determining good
  // parameter choices.
  std::vector<std::tuple<double, double>> Parameters;
  for (double gamma = 0.00001; gamma <= 1; gamma *= 5) {
      for (double nu = 0.00001; nu < max_nu; nu *= 5) {
          Parameters.push_back({gamma, nu});
      }
  }

  double accuracy = 0;

  std::mutex mutex;
  std::cout << "doing cross validation" << std::endl;
  QtConcurrent::blockingMap(
      Parameters,
      [&samples, &labels, &mutex](const std::tuple<double, double> & parameters) {
          auto [gamma, nu] = parameters;
      dlib::svm_nu_trainer<kernel_type> trainer;
      // tell the trainer the parameters we want to use
      trainer.set_kernel(kernel_type(gamma));
      trainer.set_nu(nu);

      auto acc_result = dlib::cross_validate_trainer(trainer, samples, labels, 3);

      std::unique_lock<std::mutex> lock(mutex);
      std::cout << "gamma: " << gamma << "    nu: " << nu;
      // Print out the cross validation accuracy for 3-fold cross validation
      // using the current gamma and nu.  cross_validate_trainer() returns a row
      // vector. The first element of the vector is the fraction of +1 training
      // examples correctly classified and the second number is the fraction of
      // -1 training examples correctly classified.
      std::cout << "     cross validation accuracy: "
                << acc_result;
      }
   );



  // From looking at the output of the above loop it turns out that a good value
  // for nu and gamma for this problem is 0.15625 for both.  So that is what we
  // will use.

  // Now we train on the full set of data and obtain the resulting decision
  // function.  We use the value of 0.15625 for nu and gamma.  The decision
  // function will return values
  // >= 0 for samples it predicts are in the +1 class and numbers < 0 for
  // samples it predicts to be in the -1 class.
  dlib::svm_nu_trainer<kernel_type> trainer;
  trainer.set_kernel(kernel_type(0.15625));
  trainer.set_nu(0.13);
  using dec_funct_type = dlib::decision_function<kernel_type>;
  using funct_type = dlib::normalized_function<dec_funct_type>;

  // Here we are making an instance of the normalized_function object.  This
  // object provides a convenient way to store the vector normalization
  // information along with the decision function we are going to learn.
  funct_type learned_function;
  learned_function.normalizer = normalizer; // save normalization information
  learned_function.function = trainer.train(
    samples, labels); // perform the actual SVM training and save the results

  // print out the number of support vectors in the resulting decision function
  std::cout << "\nnumber of support vectors in our learned_function is "
            << learned_function.function.basis_vectors.size() << std::endl;

    std::cout << "This is a " << labels.at(34) << " class example, the classifier output is "
            << learned_function(samples.at(34)) << std::endl;



  // To get the reduced decision function out we would just do this:
  learned_function.function = reduced2(trainer, 10).train(samples, labels);
  // And similarly for the probabilistic_decision_function:
}
