using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using static NeoSmart.TextList;
using System.Linq;

namespace CSharp.Tests
{
    [TestClass]
    public class TextListTests
    {
        private readonly List<string> Names = new List<string>()
        {
            "Meg",
            "Jo",
            "Beth",
            "Amy"
        };

        private string GenerateList(int count, string conjunction, ListFormat format, string separator = ",")
        {
            return Names.Take(count).ToTextList(conjunction, format, separator);
        }

        [TestMethod]
        public void SingleItem()
        {
            Assert.AreEqual("Meg", GenerateList(1, "and", ListFormat.OxfordSeparator, ";"));
            Assert.AreEqual("Meg", GenerateList(1, "and", ListFormat.None));
        }

        [TestMethod]
        public void TwoItems()
        {
            Assert.AreEqual("Meg and Jo", GenerateList(2, "and", ListFormat.OxfordSeparator));
            Assert.AreEqual("Meg and Jo", GenerateList(2, "and", ListFormat.None));
            Assert.AreEqual("Meg or Jo", GenerateList(2, "or", ListFormat.OxfordSeparator));
            Assert.AreEqual("Meg or Jo", GenerateList(2, "or", ListFormat.None));
        }

        [TestMethod]
        public void ThreeItems()
        {
            Assert.AreEqual("Meg, Jo, and Beth", GenerateList(3, "and", ListFormat.OxfordSeparator, ","));
            Assert.AreEqual("Meg, Jo and Beth", GenerateList(3, "and", ListFormat.None, ","));
            Assert.AreEqual("Meg; Jo; and Beth", GenerateList(3, "and", ListFormat.OxfordSeparator, ";"));
            Assert.AreEqual("Meg, Jo, or Beth", GenerateList(3, "or", ListFormat.OxfordSeparator));
            Assert.AreEqual("Meg, Jo or Beth", GenerateList(3, "or", ListFormat.None));
        }

        [TestMethod]
        public void ManyItems()
        {
            Assert.AreEqual("Meg, Jo, Beth, and Amy", GenerateList(Names.Count, "and", ListFormat.OxfordSeparator));
            Assert.AreEqual("Meg, Jo, Beth and Amy", GenerateList(Names.Count, "and", ListFormat.None));
            Assert.AreEqual("Meg, Jo, Beth, or Amy", GenerateList(Names.Count, "or", ListFormat.OxfordSeparator));
            Assert.AreEqual("Meg, Jo, Beth or Amy", GenerateList(Names.Count, "or", ListFormat.None));
        }
    }
}
